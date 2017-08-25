from vlcFileReceiver import VLCfileReceiver

class VLCfileReceiverTester():

    def __init__(self, comPort):
        self.receiver = VLCfileReceiver(comPort)

    def testReceiver(self):
        self.testConstructor()
        
    def testConstructor(self):
        assert(self.comPort == self.fileSender.comPort)
        assert(self.fileSender.baudRate = 9600)
        assert(self.fileSender.serialConnection != None)
        
if __name__ == "__main__":
    tester = VLCfileReceiver("COM16")
    tester.testReceiver()
