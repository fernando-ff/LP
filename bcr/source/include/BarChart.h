#ifndef BARCHART_H
#define BARCHART_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include<chrono>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include <string>

#include "../include/text_color.h"

using namespace std;
using namespace Color;
///value type
typedef unsigned long int value_t; 
///count type
typedef unsigned short count_t;
/**
 * @brief Read the file, stores the data and handles he
 * 
 */
class BarChart{
  private:

        struct DataItem
        {
            string time_stamp;//<! The time stamp the data was captured on. 
            string label;//<! The data label.
            string other_related_info;//<! This is any other information related to the data item that it is not going to be used in the visualization. 
            value_t value;//<! The value of the data item to be represented by a single bar in a chart.
            string category;//<! A category the data item belong to.
        };
        string title;//<! The title of the chart. 
        string label;//<! The label associated with the value portrayed in the chart.
        string source;//<! The source of information.
        set<string> categorys;

        vector<value_t> charts_quantite;
        
        vector<vector< DataItem>> charts;

        list<DataItem> list_add; // !<
        map<string, int> dictionary;
        value_t colors[14]{ 31,32,33,34,35,36,37,91,92,93,94,95,96,97 };
    public:
        void add(string time_stamp, string label, value_t value, string category)
        {
            DataItem d;
            d.time_stamp = time_stamp;
            d.label = label;
            d.value = value;
            d.category = category;
            list_add.push_back(d);
        }
        /**
         * @brief read the data file 
         * 
         * @param file_name file name
         */
        void read_txt(string file_name)
        {
            vector<DataItem> bars;//<! will stores the bars reads in the file
            ifstream file{ file_name };
            string line;//<! stores the entire line 
            // if(!file.is_open())//checks is the file is open
            // {
            //     cout << file_name << endl;
            //     cout << "Please enter with a valid file" << endl;
            //     throw invalid_argument("Invalid argument.");                
            //     return; 
            // }
            ///reading the file title  
            getline(file, line);
            title = line;
            //reading the file label
            getline(file, line);
            label = line;
            //reading the file source
            getline(file,line);
            source = line;
            // /reading empty space
            getline(file, line);
            // reading chart_size
            getline(file, line);
            int bars_quantite = stoi(line) ;

            count_t i{0};//<! counther that make possible to know that are white spaces 
            charts_quantite.push_back(bars_quantite);
            while(getline(file, line))
            {
                if(i == bars_quantite)//if this is true we the next line is a white space
                {
                    //reading white space in the file
                    getline(file, line);
                    //if we are in the end of the file, stops the read
                    if(file.eof())
                        break;
                    
                    bars_quantite = stoi(line) ;
                    charts_quantite.push_back(bars_quantite);
                    //adding bars vector to the charts vector.
                    charts.push_back( bars );
                    //cleaning the vector bars
                    bars.clear();
                    i = 0;
                    getline(file,line);

                }
                DataItem new_bar;//<! stores the data read in each line.
                stringstream ss(line);//<! stores the entire line.
                count_t j{0};//<! will help us to break the entire line by comma.
                while(getline(ss,line,','))
                {
                    if(j == 0)
                        new_bar.time_stamp = line;
                    else if(j == 1)
                        new_bar.label = line;
                    else if(j == 2)
                        new_bar.other_related_info = line;
                    else if(j == 3)
                        new_bar.value = stoi(line);
                    else if(j == 4)
                        new_bar.category = line; 
                    j++; 
                }
                //inserting the category to set of categorys.
                categorys.insert( new_bar.category );
                //adding the new bar to the bars vector
                bars.push_back(new_bar);
                i++;
            }
            charts.push_back(bars);
            file.close();
        }
        /**
         * @brief sort the data based in the data value 
         * 
         */
        void sort()
        {
            for(auto &e : charts)
            {
                std::sort(e.begin(),e.end(),[](const DataItem& b1, const DataItem& b2){
                    return b1.value > b2.value;
                });
            }
        }
        /**
         * @brief classify the data based in the data category
         * 
         */
        void classifing()
        {
            
            if(categorys.size() > 14)//if there are more than 14 categorys, don't will be color for each category
                return;
            count_t i{0};
            for(auto &e : categorys)
            {
                dictionary.insert( pair<string,value_t>(e,colors[i]) );
                i++;
            }
        }
        
        friend class Animation; //Making animation class a friend.
};

/**
 * @brief  main class that controls and processes the command line arguments, reads the data, creates the database, and controls the animation.
 * 
 */
class Animation {
        private:
        /**
         * @brief Control the game state
         * 
         */
        enum State {
            START = 0,//<! the initial state.
            WELCOME,//<!  welcome message.
            READING,//<! reading the input file.
            HANDLYING,//<! Handlying the input file.
            INPUT,//<! User input[enter]
            INPUT_RACING,//<! Prepares the data to start racing.
            RACING,//<! Animating the bar charts.
            ERROR,
            END//<! finishing the program.
        };
        State state = State::START;

        string file_name {"../data/cities.txt"}; //<! default file
        // string timeStamp;

        value_t fps { 24 };//<! fps default
        value_t amount_bars { 5 };//<! default number of bars that will be render
        // value_t chart_count { 8 };//!< 
        value_t max_bar_len = 45;//<! Arbitrary value to be the length of the largest bar.

        value_t chart_indx { 0 }; //< ! control the chart that will be render.

        BarChart bc;
    public:
        /**
         * @brief processes the command line arguments and creates the basic objects, such as the bar chart
         * 
         * @param argc 
         * @param argv 
         */
        void initialize(int argc, char const *argv[])
        {
            if(argc > 1)
            {
                bool file{true};
                for(short i{1}; i < argc;i++)
                {
                    if(strcmp(argv[i],"-b") == 0)
                    {
                        value_t input_bars = stoi(argv[i+1]);
                        if(input_bars < 1 or input_bars > 15)
                        {
                            cout << tcolor(">>> Invalid NUMBER OF BARS argument\n", BRIGHT_RED);
                            cout << tcolor("Please enter with values between 1 and 15.\n", BRIGHT_YELLOW);
                            state = State::ERROR;
                            return;
                        }
                        amount_bars = input_bars;
                        i++;
                    }
                    else if(strcmp(argv[i],"-f") == 0)
                    {
                        value_t input_fps = stoi(argv[i+1]);
                        if(input_fps < 1 or input_fps > 24)
                        {
                            cout << tcolor(">>> Invalid FPS argument\n", BRIGHT_RED);
                            cout << tcolor(">>> Please enter with values between 1 and 24.\n", BRIGHT_YELLOW);
                            state = State::ERROR;
                            return;
                        }
                        fps = input_fps;
                        i++;
                    }
                    else if(strcmp(argv[i],"-f") != 0 and strcmp(argv[i],"-b") != 0 and file)
                    {
                        file_name = argv[i];
                        ifstream file { file_name };
                        if(!file.is_open())//checks is the file is open
                        {
                            cout << tcolor(">>> Invalid FILE NAME argument\n", BRIGHT_RED);
                            cout << tcolor(">>> Please enter with a valid file.\n", BRIGHT_YELLOW);
                            state = State::ERROR;
                        }
                        file.close();
                    }
                }

            }      
        }
        
        /**
         * @brief treats all the input action.
         * 
         */
        void process_events()
        {
            if(state == State:: READING)
            {
                bc.read_txt(file_name);

            }
            else if(state == State::HANDLYING)
            {
                bc.sort();
                bc.classifing();
            }
            else if(state == State::INPUT)
            {
                string input;
                getline(cin, input);
            }
            else if(state == State::INPUT_RACING)
            {
                bc.list_add.clear();
                // if(bc.charts[chart_indx].empty())   return;
                for(auto &e : bc.charts[chart_indx])
                {
                    bc.add(e.time_stamp,e.label,e.value,e.category);
                }
                chart_indx++;

                chrono::milliseconds dura( 1000/fps );
                this_thread::sleep_for( dura );

            }
        }
        /**
         * @brief updates the animation variables and the current program state, changing it from start all the way until the end state.
         * 
         */
        void update()
        {
            if(state == State::START)
           {
               state = State::WELCOME;
           } 
            else if(state == State::WELCOME)
           {
               state = State::READING;
           }
            else if(state == State::READING)
           {
               state = State::HANDLYING;
           }
           else if(state == HANDLYING)
           {
                state = State::INPUT;
           }
            else if(state == State::INPUT)
           {
               state = State::INPUT_RACING;
           }
            else if(state == State::INPUT_RACING)
           {
                state = State::RACING;
                // if(bc.charts[chart_indx].empty())
                //     state = State::END;
           }
            else if(bc.charts[chart_indx].empty())
           {
               state = State::END;
           }
            else if(state == State::RACING)
           {
               state = State::INPUT_RACING;
           }

        }
        /**
         * @brief sends information to the standard output. Depending on the current stage, you may display a welcoming message, etc.
         * 
         */
        void render()
        {

            if(state == State::WELCOME)
            {
                cout << tcolor("==========================================\n", BRIGHT_GREEN);
                cout << tcolor("Welcome to Bar Chart Race terminal, v 1.0\n",BRIGHT_GREEN);
                cout << tcolor("Copyright(C), Selan Rodrigues\n", BRIGHT_GREEN);
                cout << tcolor("==========================================\n\n", BRIGHT_GREEN);

                cout << tcolor(">>> Preparing to read input file \"" + file_name + "\"... \n\n", Color::BRIGHT_GREEN); 
                cout << tcolor(">>> Processing data, please wait.\n\n",Color::BRIGHT_GREEN);
            } 
            else if(state == State::INPUT)
           {
                cout << 
                    tcolor(">>> Input file sucess.", Color::BRIGHT_GREEN) << 
                "\n";
                cout << 
                    tcolor(">>> We have \"", BRIGHT_GREEN) << 
                    tcolor(to_string(bc.charts.size()), BRIGHT_GREEN) <<
                    tcolor("\" charts", BRIGHT_GREEN) 
                << "\n";
                cout << 
                    tcolor(">>> Animation speed is: ", BRIGHT_GREEN) << 
                    tcolor(to_string(fps), BRIGHT_GREEN)
                <<"\n";
                cout << 
                    tcolor(">>> Bars quantite: ", BRIGHT_GREEN) << 
                    tcolor(to_string(amount_bars), BRIGHT_GREEN)
                <<"\n";
                cout << 
                    tcolor(">>> Value is: ", BRIGHT_GREEN) << 
                    tcolor(bc.label, BRIGHT_GREEN) 
                <<"\n";
                cout << 
                    tcolor(">>> # of categories found: ", BRIGHT_GREEN) <<
                    tcolor(to_string(bc.categorys.size()), BRIGHT_GREEN)
                <<"\n";
                cout << 
                    tcolor(">>> Press enter to begin the animation.", BRIGHT_GREEN) 
                << "\n\n"; 
           }
            else if(state == State::RACING)
           {
                auto it = bc.list_add.begin(); //<! iterator to the begin of the list data items that will be render
                auto biggest = bc.list_add.begin();//<! the data item with the biggest value 
                auto it_end = bc.list_add.end();//<! iterator to the end of the list data items that will be render
                // pair<value_t, value_t> axis_x_scale[5];
                
                // value_t axis_count {0};
                //render the chart title.
                cout <<"\n\n\t\t" <<  Color::tcolor( bc.title, BRIGHT_BLUE ) <<"\n\n";
                //render the time stamp chart.
                cout << "\t\t\t\tTimeStamp: " << it->time_stamp << "\n\n";

                //here we were a cross multiplication.
                for(count_t k{0}; k < amount_bars and it != it_end; k++)
                {
                    unsigned long int div_result;//stores the value of the croos mutiplication

                    if(it == biggest and biggest->value > 0)
                        div_result = max_bar_len;                       
                    else if(it->value == 0)//prevents a float exception
                        div_result = 0;
                    else
                        div_result = (it->value*max_bar_len)/biggest->value;//cross multiplication.
                      

                    for(count_t i{0}; i < div_result; i++)
                    {
                        if(bc.categorys.size() < 15)
                            cout << Color::tcolor("\u2588",bc.dictionary[it->category]);
                        else
                            cout << Color::tcolor("\u2588",Color::GREEN);
                    }                        
                    cout << "--" << it->label << "[" << it->value << "]" <<"\n\n";//render the label and the value.
                    it++;
                }
                cout << "\n";
                it--;
                // --------------- under construction -----------------------------
                // unsigned long int q;
                // if(biggest->value>100000000)
                // {
                //     biggest->value /=1000;
                //     it->value /= 1000;
                // }
                // if(it->value>100000000)
                // {
                //     it->value /= 1000;
                // }
                    
                
                // unsigned long  int min_scale;
                // if(it->value < 10)
                //     min_scale = 1;
                // else if(it->value < 100)
                //     min_scale = 10;
                // else if(it->value < 1000)
                //     min_scale = 100;
                // else if(it->value < 10000)
                //     min_scale = 1000;
                // else if(it->value < 100000)
                //     min_scale = 10000;
                // else if(it->value < 1000000)
                //     min_scale = 100000;
                // q = min_scale;
                // for(;min_scale+q< it->value;min_scale+= q);

                // unsigned long int max_scale;
                // if(biggest->value < 10)
                //     max_scale = 1;
                // else if(biggest->value < 100)
                //     max_scale = 10;
                // else if(biggest->value < 1000)
                //     max_scale = 100;
                // else if(biggest->value < 10000)
                //     max_scale = 1000;
                // else if(biggest->value < 100000)
                //     max_scale = 10000;
                // else if(biggest->value < 1000000)
                //     max_scale = 100000;
                // else if(biggest->value < 10000000)
                //     max_scale = 1000000;

                // q = max_scale;
                // for(;max_scale < biggest->value;max_scale+= q);

                // long unsigned int amplitude { (max_scale - min_scale) /5};
                // if(amplitude% 2 !=0)
                //     amplitude += 1;
                // // cout <<"max_scale: " << max_scale << " min sclae: " << min_scale<< " amplitude " << amplitude << endl;
                
                // vector<int> markups;
                // unsigned long  int scale { min_scale };
                // cout << "\nmax scale: " << max_scale << " min scale " << min_scale << " q: "<< q<<" amplitude :" << amplitude << " (max_bar*scale)/max_scale" << (max_bar*scale)/max_scale << endl;
                // cout << "+-";
                // if((max_bar*scale) < max_scale)
                //     scale += (max_bar*scale) - max_scale;
                // for(short i{1}; i <= max_bar; i++)
                // {
                //     if(i == ((max_bar*scale)/max_scale) and markups.size() < 6)
                //     {
                //         if(scale < 10)
                //             cout << "|";
                //         else if(scale < 100)
                //             cout << "|-";
                //         else if(scale < 1000)
                //             cout << "-|-";
                //         else if(scale < 10000)
                //             cout << "--|-";
                //         else if(scale < 100000)
                //             cout << "-|-";
                //         else if(scale < 1000000)
                //             cout << "-|--";
                //         else if(scale < 10000000)
                //             cout << "--|";
                //         scale += amplitude;
                //         markups.push_back(i);
                //     }
                //     else
                //     {
                //         cout << "-";
                //     }
                // }
                // cout << "->";
                
                // cout << "\n";
                // cout << "0";
                // scale = min_scale ;
                // short count{0};
                // for(short i{0}; i <=  max_bar; i++)
                // {
                //     try
                //     {
                //         if( i == markups[count] and !markups.empty())
                //         {
                //             if(scale < 1000)
                //                 cout << scale ;
                //             else if(scale < 10000)
                //                 cout << scale/1000 <<"." << (scale%1000)/100<< "k";
                //             else if(scale < 1000000)
                //                 cout << scale/1000 << "k";
                //             else if(scale < 10000000)
                //                 cout << scale/1000000 <<"." << (scale%100000)/10000<< "kk";
                //             scale += amplitude;
                //             count++;
                //          }
                //         else
                //         {
                //             cout << " ";
                //         }
                //     }
                //     catch(const std::exception& e)
                //     {
                //         std::cerr << e.what() << '\n';
                //     }
                    
                // }  

                //render the x axis
                cout <<"+";
                for(short i{0}; i < max_bar_len; i++)
                {
                    cout << "-";
                }          
                cout << "-->\n";
                cout << "0\n";
                //render the cateforys legends.
                if(bc.categorys.size() < 15 )
                {
                    cout <<"\n";
                    for(auto &e : bc.categorys)
                    cout << Color::tcolor("\u2588 ",bc.dictionary[e])<< e <<"  ";
                
                }
                cout << "\n\n";

                //render the source of the data
                cout << bc.source << endl;

           }
            else if(state == State::END)
            {
                cout << "\n\n============================\n";
                cout << "   Finishing the program\n";
                cout << "   See you next time! ;)\n";
                cout << "============================\n\n";
            }
        }
        /**
         * @brief Quit the game
         * 
         * @return true if is not the end game 
         * @return false if is the end game
         */
        bool end() { return state == State::END or state == State::ERROR; };
    friend class BarChart;
};

#endif