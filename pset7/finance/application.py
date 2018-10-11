import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    stock = db.execute("SELECT symbol FROM portfolio WHERE id=:id GROUP BY symbol;", id=session['user_id'])
    total = 0

    if stock != []:
        stocks = []
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session['user_id'])

        for symbol in stock:
            symbols = lookup(symbol['symbol'])
            shares = db.execute("SELECT SUM(amount) FROM portfolio WHERE id=:id AND symbol = :symbol;", \
            id=session['user_id'], symbol=symbols['symbol'])
            if shares[0]['SUM(amount)'] == 0:
                continue
            else:
                stockDetails = {}

                stockDetails['name'] = symbols['name']
                stockDetails['symbol'] = symbols['symbol']
                stockDetails['price'] = symbols['price']
                stockDetails['shares'] = shares[0]['SUM(amount)']
                stockDetails['total'] = stockDetails['shares'] * stockDetails['price']

                stocks.append(stockDetails)

        for i in range(len(stocks)):
            total += stocks[i]['total']
        total += cash[0]['cash']
        for i in range(len(stocks)):
            stocks[i]['price'] = usd(stocks[i]['price'])
            stocks[i]['total'] = usd(stocks[i]['total'])

        return render_template("index.html", stocks=stocks, cash=usd(cash[0]['cash']), total=usd(total))

    else:
        cash = db.execute("SELECT cash FROM users WHERE id=:user_id;", user_id=session['user_id'])
        return render_template("index.html", cash=usd(cash[0]['cash']), total = usd(cash[0]['cash']))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        try:
            symbol = lookup(request.form.get("symbol"))
            shares = int(request.form.get("shares"))
        except:
            return apology("enter some input")

        if not symbol:
            return apology("enter a valid symbol")

        if not shares or shares <= 0:
            return apology("enter the quantity of shares")

        balance = db.execute("SELECT cash FROM users WHERE id=:user_id;", user_id=session["user_id"])
        balance = int(balance[0]['cash'])
        if (shares * symbol['price']) > balance:
            return apology("can't afford")
        else:
            db.execute("INSERT INTO portfolio (symbol, amount, price, id) VALUES (:symbol, :amount, :price, :id);", \
            symbol=symbol['symbol'], amount=shares, price=symbol['price'], id=session["user_id"])

            db.execute("UPDATE users SET cash = cash-:total_price WHERE id=:user_id;", total_price=shares*symbol['price'], \
            user_id=session["user_id"])
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    stocks = db.execute("SELECT symbol, amount, price, date FROM portfolio WHERE id=:id", id=session['user_id'])

    for stock in stocks:
        stock['price'] = usd(stock['price'])

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("stock not found")
        else:
            quote['price'] = usd(quote['price'])
            return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Must provide username")

        elif not request.form.get("password"):
            return apology("Must provide password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password doesn't match")

        result = db.execute("INSERT INTO users (username, hash) \
                             VALUES(:username, :hash)", \
                             username=request.form.get("username"), \
                             hash=generate_password_hash(request.form.get("password")))

        if not result:
            return apology("Username already exist")

        session["user_id"] = result

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        try:
            symbol = lookup(request.form.get("symbol"))
            shares = int(request.form.get("shares"))
        except:
            return apology("enter some input")

        if not symbol:
                return apology("enter a valid symbol")

        if not shares or shares <= 0:
            return apology("enter the amount of shares")

        stocksOwned = db.execute("SELECT SUM(amount) FROM portfolio WHERE id=:id AND symbol=:symbol;", \
        id=session['user_id'], symbol=symbol['symbol'])
        if not stocksOwned[0]['SUM(amount)'] :
            return apology("you don't have this stock")

        if shares > stocksOwned[0]['SUM(amount)']:
            return apology("you have that many stocks")

        db.execute("INSERT INTO portfolio (symbol, amount, price, id) VALUES (:symbol, :amount, :price, :id);", \
        symbol=symbol['symbol'], amount=-shares, price=symbol['price'], id=session["user_id"])

        db.execute("UPDATE users SET cash = cash + :total_price WHERE id = :user_id;", total_price=shares*symbol['price'], \
        user_id=session["user_id"])

        return redirect('/')

    else:
        return render_template("sell.html")

def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)

# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
