import serial
import sqlite3
import time
from flask import *  
def create_connection(db_file):
    """ create a database connection to the SQLite database
        specified by the db_file
    :param db_file: database file
    :return: Connection object or None
    """
    conn = None
    try:

        conn = sqlite3.connect(db_file)
    except Error as e:
        print(e)
 
    return conn


ser = serial.Serial('COM9',9600)
ser.flushInput()

database = r"C:\sqlite\db\db1.db"


app = Flask(__name__)  

@app.route('/dts') 
def dts():
    message=[]
    conn=create_connection(database);
    # print("fff")
    ser.write(ip.encode())
    time.sleep(5)
    ids=ser.read(ser.inWaiting())
    arr=ids.decode("utf-8").split('\r\n')
    #print(arr)
    arr.remove('')
    count=int(arr[0])
    for id in arr:
        if(len(id)>4):
            id=id[1:]
            cur= conn.cursor()
            cur.execute("select status from cse where id=?",(id,))
            rows=cur.fetchall()
            if(rows[0][0]==0):
                cur.execute("select name from cse where id=?",(id,))
                name=cur.fetchall()
                print("Welcome ",name[0][0])
                m= "Welcome" + name[0][0]
                message.append(m)
                #lcdstr=name[0][0]
                #ser.write(lcdstr.encode())
                cur.execute("update cse set in_count=?, status=? where id=?",(count,1,id))
                conn.commit()
                conn.close()
                #print("updated")
            else:
                cur.execute("update cse set status=0 where id=?",(id,))
                conn.commit()
                cur.execute("select in_count from cse where id=?",(id,))
                rows=cur.fetchall()
                in_count=int(rows[0][0])
                fare=(count-in_count)*5
                cur.execute("select name from cse where id=?",(id,))
                name=cur.fetchall()
                print("Thank you", name[0][0],"for travelling...visit again")
                print("Distance travelled: ",count-in_count,"meters.")
                print("Fare: ",fare,"rupees only.")
                m1="Thank you"+ name[0][0]+"for travelling...visit again"
                m2="Distance travelled: "+count-in_count+"meters."
                m3="Fare: "+fare+"rupees only."
                op="Charge:"+str(fare)
                ser.write(op.encode())
                cur.execute("update cse set bal=bal-? where id=?",(fare,id))
                conn.commit()

                cur.execute("select bal from cse where id=?",(id,))
                balance=cur.fetchall()
                bal=int(balance[0][0])
                print("Balance Reamaining: ",bal,"rupees.")
                m4= "Balance Reamaining: "+bal+"rupees."
                conn.close()
                message.append(m1)
                message.append(m2)
                message.append(m3)
                message.append(m4)
    return render_template('demo.html',message=message)


@app.route('/')
def start():
    return render_template('index.html')

@app.route('/dtsdothtml')
def load_3d_dts():
    return render_template('3D-DTS.html')

@app.route('/lavan',methods=['GET','POST'])
def register():
    conn=create_connection(database);
    fname= request.form['fname']
    lname= request.form['lname']
    name= fname+' '+lname
    UID= request.form['uid']
    cur= conn.cursor()
    cur.execute('update cse set name=? where id=?',(name,UID))
    conn.commit()
    conn.close()
    return render_template('done2.html',name=name)

@app.route('/recharge',methods=['GET','POST'])
def recharge():
    print('entered')
    conn=create_connection(database);
    UID= request.form['uid']
    recharge = int(request.form['recharge'])
    print(type(recharge))
    cur= conn.cursor()
    cur.execute('select bal from cse where id = ?',(UID,))
    RUID_bal = cur.fetchall()
    currentbal = int(RUID_bal[0][0])
    cur.execute('update cse set bal=? where id = ?',(currentbal+recharge,UID))
    conn.commit()
    conn.close()
    return render_template('done.html')

@app.route('/demo')
def demo():
    message=[]
    return render_template('demo.html',message=message)

                
        #ids=str(ids)

        # arr=ids.decode("utf-8").split('\r\n')
        # num=arr[0].split('\r\n')
        # count=int(num[0])
        # #arr[0]=arr[0][3:]
        # arr.remove('')


if __name__ == '__main__':  
   app.run(debug = True)   
























