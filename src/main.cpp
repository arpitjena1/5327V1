#include "main.h"




void initialize() {

  leminit();
  selector::init();

}




void disabled() {
  // . . .
}



void competition_initialize() {
  // . . .
}




void autonomous() {

  if(selector::auton == 1){lemauton();}
  if(selector::auton == 2){}
  if(selector::auton == 3){}


}



void opcontrol() {
  // This is preference to what you like to drive on.
  ezdrive();
}
