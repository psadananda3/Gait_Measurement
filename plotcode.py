import numpy as np
import matplotlib.pyplot as plt
import pylab

data=np.loadtxt("sensor.txt")

sonic1=data[:,0]
prox1=data[:,1]
pir1=data[:,2]

sonic2=data[:,3]
prox2=range(1,len(data),1);
pir2=range(1,len(data),1);


fig = plt.figure()
pylab.rc('font', family='serif', size=11)
def plotsensor(ax,x):
	ax.set_xlabel('time')
	ax.set_ylabel('Sensor reading')
	ax.plot([0.25*i for i in range(0,len(x))],x, c='r', label='sensor reading',marker='.')




#ULTRASONIC1
ax1 = fig.add_subplot(321)
plotsensor(ax1,sonic1)  
ax1.legend(['ultrasonic1'],prop={'size':11})  

#PROXIMITY1
ax1 = fig.add_subplot(322)  
plotsensor(ax1,prox1) 
ax1.legend(['Proximity1'],prop={'size':11})   

#PIR1
ax1 = fig.add_subplot(323)  
plotsensor(ax1,pir1) 
ax1.legend(['PIR1'],prop={'size':11})    

#ULTRASONIC2
ax1 = fig.add_subplot(324) 
plotsensor(ax1,sonic2)  
ax1.legend(['ultrasonic2'],prop={'size':11})  

#PROXIMITY1
ax1 = fig.add_subplot(325)  
plotsensor(ax1,prox2)  
ax1.legend(['Proximity2'],prop={'size':11})   

#PIR1
ax1 = fig.add_subplot(326)    
plotsensor(ax1,pir2)   
ax1.legend(['PIR2'],prop={'size':11})   
plt.show()

