#pragma config(Motor,  port1,           frm,            tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           brm,            tmotorServoContinuousRotation, openLoop,reversed)
#pragma config(Motor,  port10,          flm,            tmotorServoContinuousRotation, openLoop,reversed)
#pragma config(Motor,  port3,           blm,            tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           am,             tmotorServoContinuousRotation, openLoop,reversed)
#pragma config(Motor,  port5,           am2,            tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           scope,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           scope2,         tmotorServoContinuousRotation, openLoop,reversed)
/*++++++++++++++++++++++++++++++++++++++++MOTOR CONFIGURATION+++++++++++++++++++++++++++++++++++++++++++++++++++++++
WARMING: BY NO MEANS EDIT THE CODE WITH '#pragma' SINCE IT WILL CONFUSE THE PROGRAM COUSING IT PERFORM INADEQUATELY*/

/*Program designed by Jose Gonzalez
	Momterrey, Mexico

MOTORS
frm -> front right motoron port 1
brm -> back right motor on port 4
flm -> front left motor on port 10
blm -> back left motor on port 3
motor 1 del brazo en puerto 6
motor 2 del brazo en puerto 5
motor scope puerto 8
motor scope2 puerto 9

AUTONOMOUS FUNCTIONS
Execute 'autonomous_LEFT()' if at left is the starting position
Execute 'autonomous_RIGHT()' if at right is the starting position
*/

//autonomous functions
void autonomous_RIGHT();
void autonomous_LEFT();
//Movement funcitons
void moveRobot(int power, int time);
void stopRobot();
void moveScope(int power, int time);
void moveArm(int power, int time);
void turnRobot(int rMotors, int lMotors, int time);
//Autonomous competition startup (uncomment the nesessary function)
void autonomousCompetition()
{
	while(vexRT[Btn8L] != 1)
		{

		}
	autonomous_LEFT();
	autonomous_RIGHT();
}
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	//Autonomous competition startup (uncomment it when necessary)
	//autonomousCompetition();

	//'While loop' for constant alternation between manual and autonomous mode
	while (true)
	{
		//Declares variable 'i' of type integer and assigns value of '1'
		int i = 0;

		//'while loop' for continuous manual movement
		//with condition 'do [code] while i's value remains equal to 1'
		while(i == 0)
	 	 {
	  	//Assigns controller channel values to respective motors
	 	  //for foward/backward movements of wheels
	    motor[frm] = vexRT[Ch2];
	    motor[brm] = vexRT[Ch2];
	    motor[flm] = vexRT[Ch3];
	    motor[blm] = vexRT[Ch3];

		//CODE FOR ARM (UPPER SCOPE)

	    //If button '6U' is pressed arm goes up
	    if (vexRT[Btn6U] == 1)
	  			{
		    		motor[am] = 127;
		    		motor[am2] = 127;
	    		}

	    //If button '6D' is pressed arm goes down
	    else if (vexRT[Btn6D] == 1)
	    		{
	    			motor [am]= -127;
	    			motor [am2]= -127;
	    		}

	    //If no button is pressed arm will stop moving
	   	else
	    		{
	    		  motor [am] = 0;
	    		  motor [am2] = 0;
	    		}

	//CODE FOR (LOWER) SCOPE

	    	//If button '5U' is pressed scope will move up
	    	if (vexRT[Btn5U] == 1)
	    	{
	    			motor[scope]= 127;
	    			motor[scope2]= 127;
	    	}

	    	//If button '5D' is pressed scope will move down
	    	else if (vexRT[Btn5D] == 1)
	    			{
	    				motor [scope]= -127;
	    				motor [scope2]= -127;
	    			}

	    	//If no button is pressed scope will stop moving
	    	else
	    			{
	    		    motor [scope] = 0;
	    		    motor [scope2] = 0;
	    		  }

					//If button '8R' is pressed, 'i' will increment by 1 OR by 2
	    		//depending on competition conditions.
	    		//Ending with a final value of 1 OR 2 (not 0) for variable 'i' exiting the 'while loop'
	    		//Increment by '1' if starting position is LEFT
	    		//Increment by '2' if starting position is RIGHT
	    		if (vexRT[Btn8R] == 1) i += 1;
	    		if (vexRT[Btn8L] == 1) i += 2;
			}

			//In case the value of 'i' is 1, task 'autonomous_LEFT' will execute
			//In case the value of 'i' is 2, task 'autonomous_RIGHT' will execute
			switch(i)
			{
				case 1:
					autonomous_LEFT();
					break;
				case 2:
				 autonomous_RIGHT();
			}


	//Execution ends and robot stops
	}
}

//++++++++++++++++++++++++++++| FUNCTIONS AREA |+++++++++++++++++

void moveRobot(int power, int time)
{
	motor[flm] = power;
	motor[blm] = power;
	motor[frm] = power;
	motor[brm] = power;
	wait1Msec(time);
	stopRobot();
}

void stopRobot()
{
	motor[flm] = 0;
	motor[blm] = 0;
	motor[frm] = 0;
	motor[brm] = 0;
	motor[scope] = 0;
	motor[scope2] = 0;
	motor[am] = 0;
	motor[am2] =0;
	wait1Msec(50);
}

void moveScope(int power, int time)
{
	motor[scope] = power;
	motor[scope2] = power;
	wait1Msec(time);
	stopRobot();
}

void turnRobot(int rMotors, int lMotors, int time)
{
		motor[frm] = rMotors;
		motor[brm] = rMotors;
		motor[flm] = lMotors;
		motor[blm] = lMotors;
		wait1Msec(time);
		stopRobot();
}

void moveArm(int power, int time)
{
	motor[am] = power;
	motor[am2] = power;
	wait1Msec(time);
	stopRobot();
}


void autonomous_LEFT()
{
			//move foward
			moveRobot(127, 1500);

			//Turn right
		 turnRobot(-127, 0, 850);

			//move backwards
			moveRobot((-127),400);

			//baja pala
			moveScope(-127, 800);

			//move foward

			moveRobot(127, 1000);

			moveScope(127, 1950);

			moveScope(-30, 20);

			moveRobot(-127, 800);

			turnRobot(-127, 127, 500);

			moveRobot(-127, 800);

			moveScope(-127,500);

			moveArm(127,2300);
}



void autonomous_RIGHT()
		{

			turnRobot(127, -127, 500);

			moveRobot(127, 400);

			turnRobot(-127, 127, 300);

			moveScope(-127, 1000);

			moveRobot(127, 1500);

			moveScope(127, 1700);

			turnRobot(127, -127, 955);

			//avanzar atras
			turnRobot(-100, -127, 500);

			moveScope(-120, 1500);

			moveArm(120, 2000);

			moveArm(-127, 500);

	}



//End of program
