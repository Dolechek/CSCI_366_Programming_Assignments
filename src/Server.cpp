//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"

/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    file->seekg(0, ios::beg);
    int start = file->tellg();
    file->seekg(0, ios::end);
    int end = file->tellg();
    return end - start;
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    this->board_size = board_size;

    /*Variables for bringing in the file*/
    ifstream ifs1;
    ifstream ifs2;

    /*Open the files*/
    ifs1.open(p1_setup_board);
    if(ifs1.fail()){
        throw ServerException("Error: Couldn't open" + p1_setup_board);
    }
    ifs2.open(p2_setup_board);
    if(ifs2.fail()){
        throw ServerException("Error: Couldn't open" + p2_setup_board);
    }
    if(get_file_length(&ifs1) != (board_size*(board_size+1))){
        throw ServerException("Error: Incorrect Board Size");
    }

    if(get_file_length(&ifs2) != (board_size*(board_size+1))){
        throw ServerException("Error: Incorrect Board Size");
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    /*Local Variables*/
    ifstream ifs;
    string line;
    vector<vector<char>> cBoard; // 2D vector of characters
    /*two if statements to check and make sure there is only 2 players*/
    if(player > 2 || player < 1){
        throw ServerException("Error: Invalid player number.");
    }
    /*make sure we aren't out of bounds*/
    if(y >= board_size || x >= board_size){
        return OUT_OF_BOUNDS;
    }

    /*checking for hits and misses*/
    /*Found the information for the 2D vector from this stack overflow link. Code used was the while loop
     * and modified it a bit to work with what I wanted it to do.
     * https://stackoverflow.com/questions/56554212/how-do-i-read-a-text-file-into-a-2d-vector
     * */
    if(player == 2){
        ifs.open("player_1.setup_board.txt");
    }else if(player == 1){
        ifs.open("player_2.setup_board.txt");
    }
    while (std::getline(ifs, line)) {
        std::vector<char> row;
        for (char &c : line) {
            if (c != '\n') {
                row.push_back(c);
            }
        }
        cBoard.push_back(row);
    }
    ifs.close(); // close the input file stream

    /*logic to register hits or misses*/
    if(cBoard[y][x] != '_')
        return HIT;
    else
        return MISS;
}


int Server::process_shot(unsigned int player) {
    /*code to open file and read in the coordinates provided by player*/
    if(player > 2 || player < 1){
        throw ServerException("Error: invalid player number");
    }

    string whoIsP = std::to_string(player); //whoIsP will be overridden by whoever just shot.
    string input_file = "player_" + whoIsP + ".shot.json"; // string will concatenate for file name set to input_file
    int x = 0,y = 0; // empty x and y variables
    ifstream ifs(input_file); // open input file stream

    /*checking to see if a shot has even been made*/
    if(!ifs){
        return NO_SHOT_FILE;
    }

    cereal::JSONInputArchive ipArchive(ifs); // initialize an archive on the file
    ipArchive(x,y); // deserialize
    ifs.close(); // close the input file stream

    /*code to write back to the JSON FILE*/
    int result = evaluate_shot(player,x,y);
    string result_file = "player_" + whoIsP + ".result.json";
    remove(result_file.c_str()); // remove serialization of file

    /* Logic to handle if player 1 or 2 was the one that shot.
     * since it wouldn't let me use whoIsP */
    if(player == 1){
        ofstream ofs(result_file);
        cereal::JSONOutputArchive opArchive(ofs);
        opArchive(CEREAL_NVP(result));
        remove("player_1.shot.json");
        return SHOT_FILE_PROCESSED;
    }else if(player == 2){
        ofstream ofs(result_file);
        cereal::JSONOutputArchive opArchive(ofs);
        opArchive(CEREAL_NVP(result));
        remove("player_2.shot.json");
        return SHOT_FILE_PROCESSED;
    }

    /* OLD CODE THAT I WAS MESSING WITH
     * if(eval == HIT){
        ofstream rfs(result_file);
        cereal::JSONOutputArchive opArchive(rfs);
        opArchive(cereal::make_nvp("result", HIT));
        rfs.close();
        return SHOT_FILE_PROCESSED;
    }else if(eval == MISS){
        ofstream rfs(result_file); //create an input stream
        cereal::JSONOutputArchive opArchive(rfs);
        opArchive(cereal::make_nvp("result", MISS));
        rfs.close();
        return SHOT_FILE_PROCESSED;
    }else if(eval == OUT_OF_BOUNDS){
        ofstream rfs(result_file);
        cereal::JSONOutputArchive opArchive(rfs);
        opArchive(cereal::make_nvp("result", OUT_OF_BOUNDS));
        rfs.close();
        return SHOT_FILE_PROCESSED;
    }*/
}