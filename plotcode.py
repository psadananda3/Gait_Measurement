import numpy as np
import matplotlib.pyplot as plt

#with open("sensorpot.txt") as f:
 #   data = f.read()

#data = data.split('\n')
data=np.loadtxt("sensor.txt")

sonic1=data[:,0]
prox1=data[:,1]
pir1=data[:,2]

sonic2=data[:,4]
prox2=data[:,5]
pir2=data[:,6]
#print data


fig = plt.figure()

def plotsensor(ax,x):
	ax.set_xlabel('time')
	ax.set_ylabel('Sensor reading')
	ax.plot([0.25*i for i in range(0,len(x))],x, c='r', label='sensor reading',marker='.')




#ULTRASONIC1
ax1 = fig.add_subplot(321)
ax1.set_title("Ultrasonic1")  
plotsensor(ax1,sonic1)  

#PROXIMITY1
ax1 = fig.add_subplot(322)
ax1.set_title("proximity1")    
plotsensor(ax1,prox1)  

#PIR1
ax1 = fig.add_subplot(323)
ax1.set_title("PIR1")    
plotsensor(ax1,pir1)  

#ULTRASONIC2
ax1 = fig.add_subplot(324)
ax1.set_title("Ultrasonic1")  
plotsensor(ax1,sonic2)  

#PROXIMITY1
ax1 = fig.add_subplot(325)
ax1.set_title("proximity1")    
plotsensor(ax1,prox2)  

#PIR1
ax1 = fig.add_subplot(326)
ax1.set_title("PIR1")    
plotsensor(ax1,pir2)   
plt.show()

