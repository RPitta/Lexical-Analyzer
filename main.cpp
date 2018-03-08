#include "projlex.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

void most_common(map<string, int> idents) {
	signed int max = 0;
	for (const auto& ident : idents) {
   		if (ident.second > max) {
   	    	max = ident.second;
		}
	}
 
 	int loopcnt = 0;
 
	for (const auto& ident : idents) {
   		if (ident.second == max) {
        	if (loopcnt == 0) {
   	    		cout << ident.first;
            	++loopcnt;
            }
        	else {
            	cout << ", " << ident.first;
            	++loopcnt;
            }
		}
	}
	cout << '\n';
}

static size_t max_length(vector<string> idents) {
	size_t max = 0;
	for (const auto& ident : idents) {
   		if (ident.length() > max) {
   	    	max = ident.length();
		}
	}
    return max;
}

int main (int argc, char** argv) {

	bool v = false;
	bool mci = false;
	bool sum = false;
	int tcount = 0;
	int scount = 0;
	int filecnt = 1;
 	int lineNumber = 0;
	string argument;
	string filename;
	ostringstream os;
	ifstream infile;
 	vector<string> s;
 	map<string, int> idents;

	// Loop through each argument, checking for possible flags.
	for( int i = 1; i < argc; ++i ) {
		if ( argv[i][0] == '-') {
			switch(argv[i][1]) {

				case 'v':
					v = true;
					break;

				case 'm':
					if (argv[i][2] == 'c') { 
						if (argv[i][3] == 'i') {
							mci = true;
						}
					}
					break;

				case 's':
					if (argv[i][2] == 'u') {
						if (argv[i][3] == 'm') {
							sum = true;
						}
					}
					break;

				default:
					cerr << "INVALID FLAG " <<  argv[i] << endl;
					return -1;

			}
		}
	}

	// The filename should be the last argument.
	filename = argv[argc - 1];
 

    // This looks for additional files, there can only be one.
    for( int i = 1; i < argc - 1; ++i ) {
        argument = argv[i];
        for( unsigned int j = 0; j < argument.length(); ++j ) {
            if (argument[j] == '.') {
                ++filecnt;
                if (filecnt > 1) {
                    cerr << "TOO MANY FILE NAMES" << endl;
                    return -1;
                }
            }
        }
    }

	// Try to open a file only if there is one. 
	if (filename[0] != '-')
	{
		infile.open( filename );
		if( !infile.is_open() ) {
			cerr << "UNABLE TO OPEN " << filename << endl;
			return -1;
		}
    }
    else {
        cerr << "YOU MUST ENTER A VALID FILENAME";
        return -1;
    }

    Token tok;
    while ( (tok = getNextToken( &infile, &lineNumber)) != DONE && tok != ERR ) {
     	
     	++tcount;
     	if (tok == SCONST) {
        	++scount;
        	s.push_back(tok.GetLexeme());
        }
     	else if (tok == IDENT) {
        	++idents[tok.GetLexeme()];
        }
    	if (v) {
        	if (tok == SCONST || tok == ICONST || tok == IDENT) {
            	cout << tok;
            }
        	else {
            	cout << tok;
            }
        }
    }
	
	if (tok == DONE) {
    	if (mci) {
        	cout << "Most Common Identifier: ";
        	most_common(idents);
        }	
    	if (sum) {
        	cout << "Total lines: " << tok.GetLinenum() << '\n';
         	cout << "Total tokens: " << tcount << '\n';
         	cout << "Total strings: " << scount << '\n';
         	cout << "Length of longest string: " << max_length(s) << '\n';
        }
	}
    	 
    if (tok == ERR) {
    	cerr << "Error on line " << tok.GetLinenum() << " (" + tok.GetLexeme() + ")\n"; 
		return -1;
    }

 return 0;

}