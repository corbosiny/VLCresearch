import serial

class VLCfileSender():

    def __init__(self, comPort, baudRate = 9600):
        self.comPort = comPort
        self.baudRate = baudRate
        self.serialConnection = serial.Serial(comPort, baudRate)
        
    def sendFile(self, fileName):
        byteData = self.getFileByteData(fileName)
        preppedData = self.prepByteData(byteData)
        preppedFileName = self.prepFileName(fileName)
        self.transmitByteData(preppedFileName)
        self.transmitByteData(preppedData)
        
    def getFileByteData(self, fileName):
        with open(fileName, 'rb') as file:
            data = file.read()
            return data

    def prepByteData(self, dataToPrep):
        preppedData = dataToPrep + b'\0'
        return preppedData

    def prepFileName(self, fileName):
        preppedFileName = fileName + '\0'
        return preppedFileName.encode('utf-8')
    
    def transmitByteData(self, byteData):
        self.serialConnection.write(byteData)
    
if __name__ == "__main__":
    fileSender = VLCfileSender("COM16")
    while(True):
        fileName = input(">>")
        fileSender.sendFile(fileName)

