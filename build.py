import glob
import os
import shutil
import tempfile
from subprocess import call

subDirs = ['utils', 'engine']

sourceFileLineStart = 'set(SOURCE_FILES'

def build():
	os.chdir('build')

	call('make -j30')

	os.chdir('..')

def writeToCmakeFile(sourceFiles):
	cmakeSet = sourceFileLineStart
	
	for file in sourceFiles:
		cmakeSet += ' ' + file
	
	cmakeSet += ')\n'

	filePath = 'CMakeLists.txt'
	fh, absPath = tempfile.mkstemp()
	with open(absPath, 'w') as newFile:
		with open(filePath) as oldFile:
			for line in oldFile:
				if sourceFileLineStart in line:
					newFile.write(cmakeSet)
				else:
					newFile.write(line)

	os.close(fh)
	os.remove(filePath)
	shutil.move(absPath, filePath)

def parseSubdir(subDir):
	if subDir == '':
		return

	os.chdir(subDir)
	sourceFiles = glob.glob('*.cpp')
	
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