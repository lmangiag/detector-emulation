## events module

## Detector response functions
def DetectorChargeResponse(inputCharge):
    return inputCharge*10

def DetectorTimeResponse(inputTime):
    return inputTime + 0.1

## Redout response functions
def ReadoutChargeResponse(inputCharge):
    return inputCharge*0.9

def ReadoutTimeResponse(inputTime):
    return inputTime + 1

## Particle Object
class Particle():
    def __init__(self, charge, time, X, Y):
        self._charge = charge
        self._eventTime = time
        self._X = X
        self._Y = Y

    def getCharge(self):
        return self._charge

    def getTime(self):
        return self._eventTime

    def getPosition(self):
        return self._X, self._Y

## DetectedParticle object
# inherits from Particle and applies Detector Response function
class DetectedParticle(Particle):
    def __init__(self, p):
        self._charge = DetectorChargeResponse(p.getCharge())
        self._eventTime = DetectorTimeResponse(p.getTime())
        self._X, self._Y = p.getPosition()

# Readout
# inherits from Particle and applies Readout System Response function
class ReadoutParticle(Particle):
    def __init__(self, p):
        self._charge = ReadoutChargeResponse(p.getCharge())
        self._eventTime = ReadoutTimeResponse(p.getTime())
        self._X, self._Y = p.getPosition()
