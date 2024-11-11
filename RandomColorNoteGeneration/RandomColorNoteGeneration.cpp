// RandomColorNoteGeneration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MidiFile.h"

using namespace std;
using namespace smf;

int main()
{
	cout << "Output file name: ";
	string filename;
	getline(cin, filename);
	cout << "Start key: ";
	uint16_t startkey;
	cin >> startkey;
	cout << "End key: ";
	uint16_t endkey;
	cin >> endkey;
	endkey++;
	cout << "PPQ: ";
	uint16_t PPQ;
	cin >> PPQ;
	cout << "Measures: ";
	size_t measures;
	cin >> measures;
	cout << "Minimum note length: ";
	uint16_t minLength;
	cin >> minLength;
	cout << "Maximum note length: ";
	uint16_t maxLength;
	cin >> maxLength;
	maxLength++;
	cout << "Minimum note velocity: ";
	uint16_t minVel;
	cin >> minVel;
	cout << "Maximum note velocity: ";
	uint16_t maxVel;
	cin >> maxVel;
	maxVel++;
	cout << "Allow CH 10: ";
	bool CH10;
	cin >> CH10;
	
	MidiFile Output;
	Output.setTicksPerQuarterNote(PPQ);
	Output.addTrack();
	MidiEventList& Track = Output[0];
	for (uint16_t Key = startkey; Key < endkey; Key++) {
		uint16_t CH;
		MidiEvent NoteOn;
		MidiEvent NoteOff;
		for (int Tick = 0; Tick < measures*4*PPQ;) {
			if (CH10) {
				CH = rand() % 16;
			}
			else {
				CH = rand() % 15;
				if (CH >= 9) {
					CH++;
				}
			}
			NoteOn.makeNoteOn(CH, Key, rand() % (maxVel-minVel) + minVel);
			NoteOn.tick = Tick;
			Tick += rand() % (maxLength-minLength) + minLength;
			NoteOff.makeNoteOff(CH, Key, 0);
			NoteOff.tick = Tick;
			Track.append(NoteOn);
			Track.append(NoteOff);
		}
	}
	Output.sortTracks();
	Output.makeDeltaTicks();
	Output.write(filename);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
