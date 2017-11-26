import matplotlib.pyplot as plt
import os
from os.path import basename
import math

class LogPlotter:
	
	__path_to_logs = '/Users/wuzzapcom/Coding/Courceworks/build-Modeling-Desktop_Qt_5_9_1_clang_64bit-Debug/Modeling.app/Contents/MacOS/'

	def __init__(self, filename = None):
		self.row_names = []
		self.lines = []

		if filename == None:
			filename = self.__pick_file()

		filename = self.__path_to_logs + filename

		csv = open(filename, 'r')
		lines = csv.readlines()
		csv.close()

		splittedLines = [line.split(',') for line in lines]
		self.row_names = splittedLines[0]

		for lineIndex in range(len(splittedLines) - 1):
			self.lines.append([float(element) for element in splittedLines[lineIndex + 1]])

	def __pick_file(self):

		files = [f for f in os.listdir(self.__path_to_logs)]
		max_timestamp = 0
		selected_filename = ''
		for f in files:
			if f.endswith('.csv'):
				if basename(f)[:-4].isdigit() and int(basename(f)[:-4]) > max_timestamp:
					max_timestamp = int(basename(f[:-4]))
					selected_filename = basename(f)

		return selected_filename


	def __getNumberFromEveryLineFromGivenPosition(self, position: int):
		return [line[position] for line in self.lines]

	def buildEnergiesPlot(self):

		W = self.__getNumberFromEveryLineFromGivenPosition(len(self.lines[0]) - 2)
		E = self.__getNumberFromEveryLineFromGivenPosition(len(self.lines[0]) - 1)
		energy = [w + e for (w, e) in zip(W, E)]
		f, (energyPlot, wPlot, ePlot) = plt.subplots(3, sharex = True)
		xValues = range(len(self.lines))

		energyPlot.set_title('Full Energy Plot')
		energyPlot.plot(W, label = "Kinetic Energy")
		energyPlot.plot(E, label = "Potentional Energy")
		energyPlot.plot(energy, label = "Full Energy")
		energyPlot.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
	           ncol=2, mode="expand", borderaxespad=0.)

		wPlot.set_title('Kinetic Energy Plot')
		wPlot.plot(W)

		ePlot.set_title('Potentional Energy Plot')
		ePlot.plot(E)
		plt.show()

	def buildPlot(self, position: int):
		yValues = self.__getNumberFromEveryLineFromGivenPosition(position)
		xValues = range(len(self.lines))
		plt.plot(xValues, yValues)
		plt.xticks(xValues, xValues)
		plt.ylabel(self.row_names[position])
		plt.xlabel('iterations')
		plt.show()

	def testLengths(self):
		csv = open(self.__path_to_logs + 'lengths.csv', 'r')
		lines = csv.readlines()
		csv.close()

		values = []

		splittedLines = [line.split(',') for line in lines]

		for lineIndex in range(len(splittedLines)):
			values.append([float(element) for element in splittedLines[lineIndex]])

		for valueRow in values:
			length = math.sqrt((valueRow[1] - valueRow[3]) * (valueRow[1] - valueRow[3]) + (valueRow[2] - valueRow[4]) * (valueRow[2] - valueRow[4]))
			print('Expected : True, got : ' + str(length == valueRow[0]))
			if (length != valueRow[0]):
				print('\tL0 ' + str(valueRow[0]))
				print('\tlength ' + str(length))


logPlotter = LogPlotter()
logPlotter.buildEnergiesPlot()






