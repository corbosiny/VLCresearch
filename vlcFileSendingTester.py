from vlcFileSender import VLCfileSender
import random

class vlcFileSendingTester():

    def __init__(self, comPort):
        self.fileSender = VLCfileSender(comPort)
        self.comPort = comPort
        
    def testFileSender(self):
        self.testConstructor()
        actualFileData, testFileData = self.testFileReading()
        self.testDataPrep(actualFileData, testFileData)
        self.testFileNamePrep()
        
    def testConstructor(self):
        assert(self.comPort == self.fileSender.comPort)
        assert(self.fileSender.baudRate = 9600)
        assert(self.fileSender.serialConnection != None)


    def testFileReading(self):
        self.makeFakeFile()
        testData = self.fileSender.getFileByteData('fakeTestFile.txt')
        realData = self.getFakeFileByteData()
        assert(testData == realData)
        return realData, testData

    def makeFakeFile(self):
        with open('fakeTestFile.txt', 'w') as file:
            file.write('testing %d' % random.randint(0, 5))

    def getFakeFileByteData(self):
        with open('fakeTestFile.txt', 'rb') as file:
            data = file.read()
            return data
        
    def testDataPrep(self, actualData, testData):
        actualData += b'\0'
        testData = self.fileSender.prepByteData(testData)
        assert(actualData == testData)

    def testFileNamePrep(self):
        preppedName = ('fakeTestFile.txt' + '\0').encode('utf-8')
        assert(preppedName == self.fileSender.prepFileName('fakeTestFile.txt'))
    
if __name__ == "__main__":
    comPort = "COM16"
    tester = vlcFileSendingTester(comPort)
    tester.testFileSender()
