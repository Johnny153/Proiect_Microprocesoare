from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk
import numpy as np
import serial as sr
from tkinter import *

#------global variables
data1 = np.array([])
data2 = np.array([])
cond = False
#-----plot data-----
def plot_data1():
    global cond, data1, data2
    
    if (cond == True):
        
        a = s.readline()
        a.decode()
        if(a[0]==2):
            a = s.readline()
            a.decode()
            if(len(data1) < 100):
                data1 = np.append(data1,float(a[0:4]))
            else:
                data1[0:99] = data1[1:100]
                data1[99] = float(a[0:4])
            #data1 = np.append(data1,float(a))
        if(a[0]==3):
            a = s.readline()
            a.decode()
            if(len(data2) < 100):
                data2 = np.append(data2,float(a[0:4]))
            else:
                data2[0:99] = data2[1:100]
                data2[99] = float(a[0:4])
            #data2 = np.append(data2,float(a))
	    
        #print(b[0])

        lines1.set_xdata(np.arange(0,len(data1)))
        lines1.set_ydata(data1)
        canvas1.draw()

        lines2.set_xdata(np.arange(0,len(data2)))
        lines2.set_ydata(data2)
        canvas2.draw()
    root.after(1,plot_data1)


def plot_start1():
    global cond
    cond = True
    s.reset_input_buffer()

def plot_stop1():
    global cond
    cond = False
    

def reverse():
    s.write(b'r')

def get_value():
    value=horizontal.get()
    if(value==1):
        s.write(b'1')
    if(value==2):
        s.write(b'2')
    if(value==3):
        s.write(b'3')
    if(value==4):
        s.write(b'4')
    if(value==5):
        s.write(b'5')
    if(value==6):
        s.write(b'6')
    if(value==7):
        s.write(b'7')
    if(value==8):
        s.write(b'8')
    if(value==9):
        s.write(b'9')
    
    

#-----Main GUI code-----
root = tk.Tk()
root.title('CPPV')
root.configure(background = 'light blue')
root.geometry("1200x730") # set the window size

#------create Plot object on GUI----------
# add figure canvas
fig1 = Figure();
ax = fig1.add_subplot(111)
fig2 = Figure();
ay = fig2.add_subplot(111)

#ax = plt.axes(xlim=(0,100),ylim=(0, 120)); #displaying only 100 samples
ax.set_title('Flame');
ax.set_ylabel('U.I')
ax.set_xlim(-0.5,100)
ax.set_ylim(0,1500)
lines1 = ax.plot([],[])[0]

ay.set_title('Ambient');
ay.set_ylabel('Lux')
ay.set_xlim(-0.5,100)
ay.set_ylim(0,1500)
lines2 = ay.plot([],[])[0]

canvas1 = FigureCanvasTkAgg(fig1, master=root)  # A tk.DrawingArea.
canvas1.get_tk_widget().place(x = 10,y=10, width = 550,height = 400)
canvas1.draw()

canvas2 = FigureCanvasTkAgg(fig2, master=root)  # A tk.DrawingArea.
canvas2.get_tk_widget().place(x = 600,y=10, width = 550,height = 400)
canvas2.draw()

label=Label(text="Counter value setting",font = ('calbiri',12))
label.place(x=510,y=560)
horizontal = Scale(root, from_=1, to=9 ,orient=HORIZONTAL)
horizontal.pack()
horizontal.place(x=530,y=580)

change_button = tk.Button(root, text = "Reverse counter", font = ('calbiri',12),command = lambda: reverse())
change_button.place(x = 520, y = 480 )

my_btn=tk.Button(root,text="Change!",font = ('calbiri',12), command=lambda:get_value())
my_btn.place(x=550,y=650)

#----------create button---------
root.update();
start1 = tk.Button(root, text = "Start", font = ('calbiri',12),command = lambda: plot_start1())
start1.place(x = 400, y = 425 )

root.update();
stop1 = tk.Button(root, text = "Stop", font = ('calbiri',12), command = lambda:plot_stop1())
stop1.place(x =800, y = 425)


#----start serial port----
s = sr.Serial('COM7',115200);
s.reset_input_buffer()

root.after(1,plot_data1)
root.mainloop()


