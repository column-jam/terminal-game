// room_layouts.h

#ifndef room_layouts_h
#define room_layouts_h

#define room_amount 4
#define height 30
#define width 120

#include <string>

std::string pause_layout[height] = {
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                     [E] Resume                                                         ",
	"                                                                                                                        ",
	"                                                     [Esc] Exit                                                         ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        ",
	"                                                                                                                        "
};

std::string room_layout[room_amount][height] = {
    {
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "########################################################XXXXXXXXX#######################################################",
        "###############################                                                          ###############################",
        "#############################                         O           O                        #############################",
        "############################                                                                ############################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "############################                                                                ############################",
        "#############################                 *WASD or arrow keys to move                  #############################",
        "###############################                     *E to interact                       ###############################",
        "########################################################################################################################",
        "########################################################################################################################",
        "########################################################################################################################"
    }, {
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "###############################                                                          ###############################",
        "#############################         O                                                    #############################",
        "############################                                                                ############################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                        O         ###########################",
        "###########################                                                                  ###########################",
        "###########################__________________________________________________________________###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "############################                                                                ############################",
        "#############################                                                              #############################",
        "###############################                                                          ###############################",
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "########################################################         #######################################################"
    }, {
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "########################################################XXXXXXXXX#######################################################",
        "###############################                                                          ###############################",
        "#############################                               /           /                  #############################",
        "############################                                                                ############################",
        "###########################                                                          /       ###########################",
        "###########################     /    /                                                       ###########################",
        "###########################                                                      /           ###########################",
        "###########################                                                                  ###########################",
        "###########################          /                                  /            /       ###########################",
        "###########################                         /                                        ###########################",
        "###########################                                                                  ###########################",
        "###########################              /                              /                    ###########################",
        "###########################                                                                  ###########################",
        "###########################                  /                              /                ###########################",
        "###########################              /                  /                        /       ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################              /                  /               /                ###########################",
        "###########################                                                                  ###########################",
        "###########################                                                                  ###########################",
        "###########################                                 ^                                ###########################",
        "###########################     /        /                  ^                                ###########################",
        "############################                                O                               ############################",
        "#############################                /      /                                      #############################",
        "###############################                                                          ###############################",
        "########################################################         #######################################################",
        "########################################################         #######################################################",
        "########################################################         #######################################################"
    }, {
        "############################################################   #########################################################",
        "############################################################   #########################################################",
        "############################################################   #########################################################",
        "########################################| |           |             | |       | |#######################################",
        "########################################| | ||| ||||| | | ||| ||||| | | | ||| | |#######################################",
        "########################################| | |   |     | | |     | | |   |   |   |#######################################",
        "########################################| | | | | ||| ||| | ||| | | ||||| | | |||#######################################",
        "########################################| |   |     | |     |   |       | | |   |#######################################",
        "########################################| ||| ||||||| | ||||| | ||||||| | | | | |#######################################",
        "########################################|   | | |   |   |     | |     | | | | | |#######################################",
        "########################################| | | | | | ||| | | ||||| ||| | | | | | |#######################################",
        "########################################| |     | |   | | | |       | | | |   | |#######################################",
        "########################################| | | ||| ||| ||| | | ||||||| | ||||| | |#######################################",
        "########################################| | |     | |     | | | |     |       | |#######################################",
        "########################################| | | ||||| ||| ||||| | | | | ||||| | | |#######################################",
        "########################################| | | |         |       | | | |   | | | |#######################################",
        "########################################| | | ||||||||||| ||||||| | | | ||| ||| |#######################################",
        "########################################|   | |           | |     |   |         |#######################################",
        "########################################||| | | ||||||||||| | ||||| | ||||||||| |#######################################",
        "########################################| | |               | | |   |       | | |#######################################",
        "########################################| | ||||||||||||||||| | | ||||||||| | | |#######################################",
        "########################################| | | |     |         | | |         |   |#######################################",
        "########################################| | | | ||||| ||||| ||| | | | ||||| | |||#######################################",
        "########################################|   | |   |     |     |   | |       | | |#######################################",
        "########################################| ||| ||| ||||| | | ||| ||| | | ||| | | |#######################################",
        "########################################|       |         |           |         |#######################################",
        "############################################################   #########################################################",
        "############################################################   #########################################################",
        "############################################################   #########################################################",
        "############################################################   #########################################################"
    }
};

#endif // room_layouts_h