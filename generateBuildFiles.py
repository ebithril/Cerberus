import glob
import os
import shutil
import tempfile

subDirs = ['utils', 'engine', 'thirdparty']

sourceFileLineStart = 'set(SOURCE_FILES'


debug = False

def writeToFile(file, line):
        if debug == True:
                print(line[:-1])
        else:
                file.write(line)

def build():
        os.chdir('build')

        os.chdir('..')

def writeToCmakeFile(sourceFiles):
        cmakeSet = sourceFileLineStart

        for file in sourceFiles:
                cmakeSet += ' ' + file

        cmakeSet += ')\n'

        filePath = 'CMakeLists.txt'
        fh, absPath = tempfile.mkstemp()
        with open(absPath, 'w') as newFile:
                with open(filePath, 'r') as oldFile:
                        for line in oldFile:
                                if sourceFileLineStart in line:
                                        writeToFile(newFile, cmakeSet)
                                else:
                                        writeToFile(newFile, line)

        os.close(fh)
        
        if debug == False:
                os.remove(filePath)
                shutil.move(absPath, filePath)

def parseSubdir(subDir):
        if subDir == '':
                return

        if debug == True:
                print('================================ Started writing ' + subDir + ' ===============================')

        os.chdir(subDir)
        sourceFiles = glob.glob('*.cpp')
        sourceFiles.extend(glob.glob('*.c'))
        
        writeToCmakeFile(sourceFiles)

        os.chdir('..')

def main():
        sourceFiles = glob.glob('*.cpp')
        writeToCmakeFile(sourceFiles)

        for subDir in subDirs:
                parseSubdir(subDir)

        build()


if __name__ == '__main__':
        main()
