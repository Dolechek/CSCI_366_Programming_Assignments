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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    Client::player = player;// this allows me to access 'player' in lower functions

    vector<vector<int>> iBoard; // creating 2d vector of ints
    iBoard.resize(board_size, vector<int>(board_size, 0)); // filling vector w/ 0's

    string whoIsP = std::to_string(player); // whoIsP will change values depending on player 1 or 2
    string fname = "player_" + whoIsP + ".action_board.json"; // fname holds whichever player_#.action_board.json is

    ofstream array_ofp(fname); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
    write_archive(cereal::make_nvp("board", iBoard)); // serialize the data giving it a name

    initialized = true; // I don't believe this is needed just yet. but here either way.
}


void Client::fire(unsigned int x, unsigned int y) {
    string whoIsP = std::to_string(player); // whoIsP will change values depending on player 1 or 2
    string fname = "player_" + whoIsP +".shot.json"; // fname holds whichever player_#.action_board.json is

    ofstream ofs(fname); // create an output file stream
    cereal::JSONOutputArchive opArchive(ofs); // initialize an archive on the file
    /*https://stackoverflow.com/questions/47297648/using-cereal-to-deserialize-a-json-string
     * found the CEREAL_NVP here. */
    opArchive(CEREAL_NVP(x), CEREAL_NVP(y)); // serialize the data
}


bool Client::result_available() {
}


int Client::get_result() {
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
}