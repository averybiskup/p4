#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
	// TODO
}

StudentTextEditor::~StudentTextEditor()
{
	// TODO
}

bool StudentTextEditor::load(std::string file) {
    ifstream infile(file);
    string d;
    
    while (getline(infile, d)) {
        if (d[d.size() - 1] == '\r')
            d.erase(d.size() - 1);
        lineList.push_back(d);
    }

	return true;  // TODO
}

bool StudentTextEditor::save(std::string file) {
    ofstream outfile(file);
    
    if (! outfile)
        return false;

    for (auto i : lineList) {
        outfile << i << endl;
    }

    return true;
}

void StudentTextEditor::reset() {
	// TODO
}

void StudentTextEditor::move(Dir dir) {

    auto it = lineList.begin();

    int maxWidth;


    switch(dir) {
        case RIGHT:
            advance(it, curRow);
            maxWidth = (*it).size();

            if (curCol > maxWidth)
                break;
            if (curCol < maxWidth)
                curCol++; 
            else {
                if (curRow < lineList.size()-1) {
                    curCol = 0;
                    curRow++;
                }
            }
            break;
        case LEFT:
            advance(it, curRow-1);
            maxWidth = (*it).size();
            if (curCol == 0 && curRow != 0) {
                curRow--;
                curCol = maxWidth;
            } else 
                curCol--;
                
            break;
        case DOWN:
            advance(it, curRow+1);
            maxWidth = (*it).size();
            if (curRow < lineList.size()-1)
                curRow++; 
            if (maxWidth < curCol)
                curCol = maxWidth;
            break;
        case UP:
            advance(it, curRow-1);
            maxWidth = (*it).size();
            if (curRow != 0)
                curRow--; 
            if (maxWidth < curCol)
                curCol = maxWidth;
            break;
        case HOME:
            curRow = 0;
            break;
        case END:
            advance(it, curRow-1);
            maxWidth = (*it).size();
            curRow = maxWidth;
            break;
    }
}

void StudentTextEditor::del() {
    auto it = lineList.begin();
    advance(it, curRow);

    string::iterator strIt;

    strIt = (*it).begin() + curCol - 1;
    (*it).erase(strIt);

    if (curCol >= (*it).size())
        curCol--;
}

void StudentTextEditor::backspace() {
    auto it = lineList.begin();
    advance(it, curRow);

    string::iterator strIt;

    strIt = (*it).begin() + curCol - 1;
    (*it).erase(strIt);
    curCol--;
}

void StudentTextEditor::insert(char ch) {

    list<string>::iterator i = lineList.begin();
    if (lineList.size() == 0) {
        lineList.insert(i, string(1, ch));
        curCol++;
    } else {
        auto it = lineList.begin();
        advance(it, curRow);

        (*it).insert(curCol, 1, ch);
        curCol++;
    }

}

void StudentTextEditor::enter() {
	// TODO
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = curRow; col = curCol; // TODO
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    lines.clear();

    for (auto it : lineList)
        lines.push_back(it);
    
	return lines.size(); // TODO
}

void StudentTextEditor::undo() {
	// TODO
}
