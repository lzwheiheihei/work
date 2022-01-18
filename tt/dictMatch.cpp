//
// Created by lzw on 2022/1/17.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

enum TYPE {
    MUSIC_AND_MOVIE = 1,
    MOVIE = 2,
    MUSIC = 3
};
#define MUSIC_AND_MOVIE_STR "-*音乐&电影*-"
#define MOVIE_STR "-*电影*-"
#define MUSIC_STR "-*音乐*-"

std::unordered_map<std::string, TYPE> dict_map;
std::vector<std::string> video_title_vec;
int max_key_len = 0;
//可以多线程优化
void read_dict_file() {
    std::ifstream infile("/Users/liuziwei/Documents/tt_code/hackercup_contest_1/dict.txt");
    std::string data;
    while (std::getline(infile, data)) {
        for (int i = 0; i < data.size(); i++) {
            max_key_len = std::max(i, max_key_len);
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
    std::ifstream infile("/Users/liuziwei/Documents/tt_code/hackercup_contest_1/video_title.txt");
    std::string line;
    while (std::getline(infile, line)){
        video_title_vec.push_back(line);
    }
    infile.close();
}

void replace(std::string &video_title){
    int before_pos = 0; //上个被替换的位置
    std::string new_str;
    for (int i = 0; i < video_title.size(); i++){
        std::string str = std::string(video_title.begin()+before_pos, video_title.begin()+i);//从上个位置到当前位置
        if (dict_map.find(str) != dict_map.end()) {
            if (max_key_len < str.size()) {
                std::string expand_str = std::string(str.begin()+str.size()-before_pos, str.end());
                if (dict_map.find(expand_str) != dict_map.end()){
                    std::string replaced_str;
                    TYPE res = dict_map[expand_str];
                    switch (res) {
                        case MUSIC_AND_MOVIE:
                            replaced_str = MUSIC_AND_MOVIE_STR;
                            break;
                        case MUSIC:
                            replaced_str = MUSIC_STR;
                            break;
                        case MOVIE:
                            replaced_str = MOVIE_STR;
                            break;
                    }
                }
//                expand_str =
            } else {
                std::string replaced_str;
                TYPE res = dict_map[str];
                switch (res) {
                    case MUSIC_AND_MOVIE:
                        replaced_str = MUSIC_AND_MOVIE_STR;
                        break;
                    case MUSIC:
                        replaced_str = MUSIC_STR;
                        break;
                    case MOVIE:
                        replaced_str = MOVIE_STR;
                        break;
                }
            }

        }
    }
}

int main(){
    read_dict_file();
    int line = 0;
    for(std::unordered_map<std::string, TYPE>::iterator it = dict_map.begin(); it != dict_map.end(); it++) {
        std::cout << line++ << " " << it->first << " " << it->second << std::endl;
    }
    std::cout << max_key_len;
    read_video_title_file();
    for (int i = 0; i < 10; i++){
        replace(video_title_vec[i]);
    }
}
