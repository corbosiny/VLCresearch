import serial

class VLCfileReceiver():

    def __init__(self, comPort, baudRate = 9600):
        self.comPort = comPort
        self.baudRate = baudRate
        self.serialConnection = serial.Serial(comPort, baudRate)

    def receiveFile(self):
        fileName = self.receiveFileName()
        fileByteData = self.receiveFileByteData()
        self.createAndWriteToFile(fileName, fileByteData)

    def receiveFileName(self):
        fileName = bytes()
        lastCharacterReceived = b''
        while lastCharacterReceived != b'\0':
            fileName += lastCharacterReceived
            lastCharacterReceived = self.serialConnection.read()
            
        print("Receiving:", fileName.decode('utf-8'))
        return fileName.decode('utf-8')

    def receiveFileByteData(self):
        bytesFromFile = bytes()
        lastByteReceived = b''
        while lastByteReceived != b'\0':
            bytesFromFile += lastByteReceived
            lastByteReceived = self.serialConnection.read()
        return bytesFromFile

    def createAndWriteToFile(self, fileName, fileByteData):
        with open(fileName, 'wb') as file:
            file.write(fileByteData)

if __name__ == "__main__":
    receiver = VLCfileReceiver("COM16")
    while(True):
        receiver.receiveFile()
