#!/usr/bin/python

#########################################################################################
#   CENTRE FOR BIOINFORMATICS, BIOMARKER-DISCOVERY & INFORMATION-BASED MEDICINE
#   THE UNIVERSITY UNIVERSITY OF NEWCASTLE
#   University Drive, Callaghan, NSW, 2308, AUSTRALIA
#
#   Script for converting a dataset from IBM format to TitanicOR's
#
#   Usage: ./ibm2titanicor.py <inputFile> [-o <outputfile>]
#         
#   Created on: 2013/04/22
#   Author: Renato Vimieiro
#                          
#   License: MIT <http://opensource.org/licenses/MIT>
#
#   Copyright (c) 2013 Renato Vimieiro
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
#   and associated documentation files (the "Software"), to deal in the Software without restriction, 
#   including without limitation the rights to use, copy, modify, merge, publish, distribute, 
#   sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all copies or 
#   substantial portions of the Software.
#
#   1 - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
#   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
#   PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
#   FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
#   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
#   SOFTWARE.
#
#   2 - EXCEPT AS CONTAINED IN THIS NOTICE, THE NAME(S) OF THE ABOVE COPYRIGHT HOLDERS SHALL NOT BE 
#   USED IN ADVERTISING OR OTHERWISE TO PROMOTE THE SALE, USE OR OTHER DEALINGS IN THIS SOFTWARE 
#   WITHOUT PRIOR WRITTEN AUTHORIZATION.
#############################################################################################

import sys
import argparse

###
# Parse arguments
def argparser():
    parser = argparse.ArgumentParser(description='Convert files from IBM to TitanicOR format')
    parser.add_argument("filename",metavar="inputFile",help="Input file (mandatory)")    
    parser.add_argument("-o","--output",metavar="outputfile",dest="outputfile",help="Output file (default stdout)",default="")
    return parser

def main():
    parser = argparser()
    args = parser.parse_args()

    try:
       nbFeat = -1
       with open(args.filename) as f:
            input = [[int(a) for a in line.strip().split()] for line in f]
            for k in range(0,len(input)):
               input[k] = input[k][3:]
               nbFeat = max(nbFeat,*input[k])
       if args.outputfile == "":
               print "{0} {1}".format(nbFeat+1,len(input)) #Format => <nbFeat> <nbSamples>\n
               print "\n".join(["{0} {1}".format(len(row),' '.join(map(str,row))) for row in input]) #Format => <length> <f1> ... <fn>       
       else:
           with open(args.outputfile,"w") as f:
               f.write("{0} {1}\n".format(nbFeat+1,len(input))) #Format => <nbFeat> <nbSamples>\n
               f.write("\n".join(["{0} {1}".format(len(row),' '.join(map(str,row))) for row in input])) #Format => <length> <f1> ... <fn>

    except Exception as e:
    	print >>sys.stderr, "Oops, something wrong!", e
    	print >>sys.stderr, sys.exc_info()
    	sys.exit(0)
       
       
       
if __name__ == '__main__':
   main()

