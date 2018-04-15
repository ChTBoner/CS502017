import sqlite3
#from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter = facilitate print values in USD
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
#db = SQL("sqlite:///finance.db")
# option check_same_thread=False added cause error "SQLite objects created in a thread can only be used in that same thread"
dbase = sqlite3.connect("finance.db", check_same_thread=False)
db = dbase.cursor() # to remove when sending to cs50

@app.route("/")
@login_required
def index():
    return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        # check for mistakes by user
        if not request.form.get("symbol") or not request.form.get("number"):
            flash("You did not provide a Symbol or a number of stocks to buy")
            return redirect(url_for("buy"))
        # quote via the Yahoo API
        else: 
            quote = lookup(request.form.get("symbol"))
            total = int(request.form.get("number")) * quote["price"]
            
            # check user current amount of money
            user_cash = db.execute("SELECT cash FROM users WHERE username = :username", (session["user_id"], )).fetchall()
            # print(user_cash[0][0], type(user_cash[0][0]))
            
            cash_left = user_cash[0][0] - total
            
            # update user's portfolio
            # check if already bought this stock before exists
            previously_owned_stock = db.execute( "SELECT * FROM portfolio WHERE ")
            

            # update stocks in db.
            # update user's cash in db
            # update user's history
            db.execute( "UPDATE users SET cash = :cash WHERE username = :username", { "cash": cash_left, "username": session["user_id"] } )
            
            dbase.commit()
            return render_template("bought.html", number=request.form.get("number"), name=quote["name"], total_amount=total)
    
    else : return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        # !! db.execute part of CS50 library.
        ''' 
            after creating a connection needs a "cursor"
            db = dbase.cursor()
        '''
        # probably to change
        #rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        rows = db.execute("SELECT * FROM users WHERE username = :username", (request.form.get("username"), )).fetchall()
        
        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0][2]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0][1]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # check if stock symbol is provided
        if not request.form.get("symbol"):
            return apology("no symbol")
        # check if stock symbol exists and display information
        else:
            quote = lookup(request.form.get("symbol"))
            print(quote)
            if not quote:
                return apology("Symbol does not exist")
            else: 
                return render_template("quoted.html", symbol=quote["symbol"], price=quote["price"], name=quote["name"])
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    # if method is POST = go through options= correct args + check password
    if request.method == "POST":
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted and confirmed
        elif not request.form.get("password") or not request.form.get("password-check"):
            return apology("must provide and confirm password")

        elif request.form.get("password") != request.form.get("password-check"):
            return apology("Password and Confirmation are different")

        # check if username already taken
        elif (request.form.get("password") == request.form.get("password-check")):
            db.execute("SELECT * FROM users WHERE username = :username", (request.form.get("username"), ))
            # db.execute("SELECT * FROM users WHERE username = ?")
            data = db.fetchone()

            # add to database, encrypting passwd
            if data is None:
                db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)", { "username": request.form.get("username"), "hash": pwd_context.encrypt(request.form.get("password"))})
                dbase.commit()
                return render_template("login.html")
            else :
                return apology("Username already exists!")

    # else method is GET
    else :
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    return apology("TODO")
