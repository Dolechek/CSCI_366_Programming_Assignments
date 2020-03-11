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
        Client::player = player;
        vector<vector<int>> iBoard;
        iBoard.resize(board_size, vector<int>(board_size, 0));
        string whoIsP = std::to_string(player);
        string fname = "player_" + whoIsP + ".action_board.json";
        ofstream array_ofp(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", iBoard)); // serialize the data giving it a name
        initialized = true;

}


void Client::fire(unsigned int x, unsigned int y) {
    string whoIsP = std::to_string(player);
    string fname = "player_" + whoIsP +".shot.json";
    ofstream array_ofp(fname); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp);
    write_archive(CEREAL_NVP(x), CEREAL_NVP(y));
}


bool Client::result_available() {
    //looking for a return of true or false, just make sure the file exists and return true if so
    string whoIsP = std::to_string(player);
    string fname = "player_" + whoIsP +".result.json";
    ifstream ifs(fname);
    if(ifs.good()){
        return true;
    } else {
        return false;
    }

}


int Client::get_result() {

    string whoIsP = std::to_string(player);
    string fname = "player_" + whoIsP +".result.json";
    ifstream ifs(fname);

    
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {

}


string Client::render_action_board(){

}