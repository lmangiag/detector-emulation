import events
import random
import time
import queue

## Helper function to provide input
def generateInput():
    chargeGen = random.random()*10  # These lines can be substituted to
    timeGen = random.random()       # input data from a different source
    X = random.random()             #
    Y = random.random()             #
    return chargeGen, timeGen, X, Y

# Initialization and parameters
N = 10                              # Number of events generated
eventID = 0                         # Initialize event Identifier

#
eventChain = queue.Queue()          # Instantiate Containters
detectorChain = queue.Queue()       #
readoutChain = queue.Queue()        #
eventDict = {}                      #

# Run
for i in range(N):
    inputCharge, inputTime, inputX, inputY = generateInput()
    eventChain.put(events.Particle(inputCharge, inputTime, inputX, inputY))
    detectorChain.put(events.DetectedParticle(eventChain.get()))
    readoutChain.put(events.ReadoutParticle(detectorChain.get()))
    eventDict["{0:06d}".format(eventID)] = readoutChain.get()
    eventID += 1

print("Events with readout output higher than 50:")
print("Charge\tTimeStamp")
for eventObj in eventDict.values():
    Chg = eventObj.getCharge()
    if  Chg >= 50:                  # print charge value if it is higher than
        print("{0:.2f}\t{1:.4f}".format(Chg,eventObj.getTime()))
