//
// Created by lzw on 2022/1/17.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

#define MUSIC_AND_MOVIE 1
#define MOVIE 2
#define MUSIC 3
#define MUSIC_AND_MOVIE_STR "-*音乐&电影*-"
#define MOVIE_STR "-*电影*-"
#define MUSIC_STR "-*音乐*-"

typedef std::unordered_map<std::string, int> DIC_MAP;
std::unordered_map<std::string, int> dict_map;
std::vector<std::string> video_title_vec;
int max_str_len = 0;
void read_dict_file() {
    std::ifstream infile("/Users/liuziwei/Documents/tt_code/hackercup_contest_1/dict.txt");
    std::string data;
    while (std::getline(infile, data)) {
        for (int i = 0; i < data.size(); i++) {
            max_str_len = std::max(i, max_str_len);
            if (data[i] == '\t') {
                std::string k = std::string(data.c_str(), i);
                std::string v = std::string(data, i+1);
                if (v == MUSIC_AND_MOVIE_STR) {
                    dict_map[k] = MUSIC_AND_MOVIE;
                } else if (v == MOVIE_STR) {
                    dict_map[k] = MOVIE;
                } else if (v == MUSIC_STR) {
                    dict_map[k] = MUSIC;
                } else {
                    std::cout << "type error";
                }
                break;
            }
        }
    }
    infile.close();
}

void read_video_title_file(){
    std::ifstream infile("/Users/liuziwei/Documents/tt_code/hackercup_contest_1/video_title.txt.bak");
    std::string line;
    while (std::getline(infile, line)){
        video_title_vec.push_back(line);
    }
    infile.close();
}

std::string replace(std::string &str) {
    std::string new_str;
    for (int i = 0; i < str.size(); )
    {
        int idx = i;
        for (int j = i; j < str.size(); j++)
        {
            std::string substr = std::string(str.begin() + i, str.begin() + j);
            if (dict_map.find(substr) != dict_map.end()) {
                idx = j;
            }
            if (j - i > max_str_len) {
                break;
            }
        }
        if (idx != i){
            std::string substr = std::string(str.begin() + i, str.begin() + idx);
            int replaced_type = dict_map[substr];
            std::string replaced_str;
            if (replaced_type == MUSIC){
                replaced_str = MUSIC_STR;
            } else if (replaced_type == MOVIE) {
                replaced_str = MOVIE_STR;
            } else if (replaced_type == MUSIC_AND_MOVIE)
                replaced_str = MUSIC_AND_MOVIE_STR;
            new_str = new_str + replaced_str;
            i = idx;
        } else {
            std::string substr = std::string(str.begin()+i, str.begin()+i+1);
            new_str = new_str + substr;
            i++;
        }
    }
    return new_str;
}

int main(){
    read_dict_file();
    read_video_title_file();
    std::ofstream out;
    out.open("result.txt", std::ios::app);
    if (!out) {
       std::cout << "error open file result.txt";
    }
    for (int i = 0; i < video_title_vec.size(); i++){
        out << replace(video_title_vec[i]) << std::endl;
    }
    std::cout << "success" << std::endl;
}
