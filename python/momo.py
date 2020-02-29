import string,random
import os
import pickle

class movie:

    def __init__(self):
        self.mname=''
        self.mcast=''
        self.mplot=''
        self.mtime=[]
        self.mbaseprice=0

    def getdata(self):
        self.mname=raw_input('Enter name of movie: ')
        self.mcast=raw_input('Enter cast with each person seperated by two spaces: ')
        self.mplot=raw_input('Enter plot summary: ')
        for i in range(4):
            x=raw_input('Enter show timing in 24 hour format: ')
            self.mtime.append(x)
        self.mbaseprice=input('Enter base price of ticket: ')
        print

    def display(self):
        print "|%s|\t%s|\t%d|\t%s|" %(self.mname,self.mtime,self.mbaseprice,self.mcast),self.mplot[0:33]
        print " "*97,self.mplot[33:]
        print "|          |                                       |               |                             |",self.mplot[33:]

        
def append():
    f=open('movie.dat','ab')
    m=movie()
    m.getdata()
    pickle.dump(m,f)
    f.close()

def show():
    if os.path.isfile('movie.dat'):
        f=open('movie.dat','rb')
        print "_"*132
        print "|MOVIE NAME|\t\tMOVIE TIME\t\t    |\tMOVIE PRICE|\tMOVIE CAST\t\t |","MOVIE PLOT                       |"
        print "_"*132
        try:
            while True:
                x=pickle.load(f)
                x.display()
        except EOFError:
            pass
    else:
        print 'File does not exist'

def search():
    if os.path.isfile('movie.dat'):
        f=open('movie.dat','rb')
        name=raw_input('Enter name of movie to be searched: ')
        try:
            while True:
                x=pickle.load(f)
                if name.lower()==x.mname.lower():
                    print 'Movie found'
                    x.display()
                    break
        except EOFError:
            print 'Movie not found'

def delete():
    if os.path.isfile('movie.dat'):
        f=open('movie.dat','rb')
        g=open('temp.dat','wb')
        name=raw_input('Enter name of movie to be deleted: ')
        try:
            while True:
                x=pickle.load(f)
                if name.lower()!=x.mname.lower():
                    pickle.dump(x,g)
        except EOFError:
            pass
        f.close()
        g.close()
        os.remove('movie.dat')
        os.rename('temp.dat','movie.dat')
    else:
        print 'File does not exist'

def update():
    if os.path.isfile('movie.dat'):
        f=open('movie.dat','rb')
        g=open('temp.dat','wb')
        name=raw_input('Enter name of movie to be updated: ')
        
        try:
            while True:
                x=pickle.load(f)
                if x.mname.lower()!=name.lower():
                    pickle.dump(x,g)
                else:
                    y=movie()
                    y.getdata()
                    pickle.dump(y,g)
        except EOFError:
            pass
        f.close()
        g.close()
        os.remove('movie.dat')
        os.rename('temp.dat','movie.dat')
        print 'New movie data is: '
        y.display()
    else:
        print 'File does not exist'

def custlist():
    if os.path.isfile('cust.dat'):
        f=open("cust.dat")
        c=customer()
        print "TICKET REFERENCE\tCUSTOMER NAME\tMOVIE NAME\tNO of TICKETS\tPRICE"
        try:
            while True:
                c=pickle.load(f)
                print "%12s\t%16s\t%10s\t%13s\t%5d" %(c.ticketref,c.cname,c.mname,c.seatno,c.tprice)
        except EOFError:
            pass
        f.close()
    else:
        print "No Bookings Done"

        
class customer:

    def __init__(self):
        self.cname=''
        self.cnum=0
        self.cemail=''
        self.seattype=''
        self.seatno=0
        self.mname=''
        self.mtime=''
        self.price=0
        self.tprice=0

    def inputdata(self):
        self.cname=raw_input('Enter customer name:')
        self.cnum=raw_input('Enter your contact number:')
        self.cemail=raw_input('Enter your e-mail id:')
        show()
        self.movie()
        self.seattype=raw_input('Enter seat type ( normal/vip )')
        self.seatno=input('Enter number of seats: ')
        self.calcprice()
        self.ticketref=self.mname[0:1]+str(random.randint(10000,20000))
        print "PLEASE NOTE YOUR BOOKING REFERNCE CODE TO VIEW THE TICKET",self.ticketref

    def movie(self):
        self.mname=raw_input('Select your movie:')
        f=open("movie.dat","rb")
        m=movie()
        flag=0
        while True:	
            try:
                while True:
                    m=pickle.load(f)
                    if self.mname==m.mname:
                        self.mtime=raw_input("Enter the time ")
                        self.price=m.mbaseprice
                        flag=1
                        break
            except EOFError:
                print "Enter a movie name from the list of movies shown above"
                self.mname=raw_input('Select your movie:')
            if flag==1:
                break
        f.close()

    def calcprice(self):
        if self.seattype.lower()=='vip':
            self.price+=30
        self.tprice=self.price*self.seatno

    def ticket(self):
        print 'Customer name:',self.cname
        print 'Phone number:',self.cnum
        print 'Customer E-mail ID:',self.cemail
        print 'Movie Name:',self.mname
        print 'Movie Time:',self.mtime
        print 'Seat type:',self.seattype
        print 'Price per seat:', self.price
        print 'Number of seats:',self.seatno
        print 'Total price:',self.tprice

def addcustomer():
    f=open("cust.dat","ab")
    c=customer()
    c.inputdata()
    pickle.dump(c,f)
    f.close()

def viewticket():
    bref=raw_input("Enter your booking reference code")
    c=customer()
    f=open("cust.dat","rb")
    try:
        while True:
            c=pickle.load(f)
            if c.ticketref==bref:
                c.ticket()
                break
    except EOFError:
        pass
    f.close()

    
ch='yes'
while ch.lower()=='yes':
    print 'Welcome message'
    user=input('ENTER\n1. FOR ADMIN MENU OPTIONS\n2. FOR CUSTOMER MENU OPTIONS\n')
    if user==1:
        print 'WELCOME ADMIN........'
        while 1<2:
            opt=input('ENTER \n1. FOR ADDING MOVIE\n2. FOR SEARCHING MOVIE\n3. FOR UPDATING MOVIE\n4. FOR DELETING MOVIE\n5. FOR DISPALYING MOVIE\n6. FOR DISPLAYING BOOKED TICKETS INFO\n0. FOR EXITING ADMIN MENU\n')
            if opt==1:
                append()
            elif opt==2:
                search()
            elif opt==3:
                update()
            elif opt==4:
                delete()
            elif opt==5:
                show()
            elif opt==6:
                custlist()
            elif opt==0:
                break
    elif user==2:
        c=customer()
        ch1='yes'
        while ch1.lower()=='yes':
            print "1.BOOK A TICKET\n2.VIEW TICKET\n"
            opt1=input('Enter your choice ')
            if opt1==1:
                addcustomer()
            elif opt1==2:
                viewticket()
            else:
                print "Invalid choice"
            ch1=raw_input("ENTER \'yes\' TO CONTINUE WITH CUSTOMER MENU OR \'no\' TO GO BACK TO MAIN MENU\n")
    else:
        print "INVALID CHOICE"
    ch=raw_input('DO YOU WISH TO CONTINUE WITH PROGRAM? ')
print 'THANK YOU FOR USING THIS PROGRAM'
