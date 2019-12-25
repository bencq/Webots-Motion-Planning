// File:          avoid.java
// Date:
// Description:
// Author:
// Modifications:

// You may need to add other webots classes such as
//  import com.cyberbotics.webots.controller.DistanceSensor;
//  import com.cyberbotics.webots.controller.Motor;
import com.cyberbotics.webots.controller.Robot;

import javafx.util.Pair;

import com.cyberbotics.webots.controller.Motor;
import com.cyberbotics.webots.controller.GPS;
import com.cyberbotics.webots.controller.Keyboard;
import com.cyberbotics.webots.controller.Compass;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

import com.cyberbotics.webots.controller.DistanceSensor;

class Point
{
	double x;
	double z;

	public Point(double x, double z)
	{
		super();
		this.x = x;
		this.z = z;
	}
	
	public double getLength()
	{
		return Math.sqrt(x * x + z * z);
	}
	
	public void normalize()
	{
		double len = this.getLength();
		this.x /= len;
		this.z /= len;
	}
	
	public static Point minus(Point p1, Point p2)
	{
		return new Point(p1.x - p2.x, p1.z - p2.z);
	}

}

public class Heuristic
{
	static double angle(Point p1, Point p2)
	{
		return modDouble(Math.atan2(p2.z, p2.x) - Math.atan2(p1.z, p1.x), 2.0 * Math.PI);
	}
	static double modDouble(double a, double m)
	{
		double div = Math.floor(a / m);
		double r = a - div * m;
		if(r < 0.0) r += m;
		return r;
	}
	


	public static void readRoute() throws IOException
	{
		File file_route = new File(new File(new File(Heuristic.class.getResource("").getPath()).getParentFile().getParentFile(), "algorithm"), "route.txt");
		Scanner scanner = new Scanner(file_route);

		while (scanner.hasNext())
		{
			double x = scanner.nextDouble();
			double z = scanner.nextDouble();
			points.add(new Point(x, z));
		}
		scanner.close();
	}
	
	final static double DS_VALUE = 1024.0;
	
	final static double MAX_SPEED = Math.PI * 2;
	static boolean handControl = false;
	static ArrayList<Point> points = new ArrayList<>();
	static Random random = new Random();
	static boolean meetObstacle = false;

	public static void main(String[] args) throws IOException
	{

		// initialize
		readRoute();
		
		// create the Robot instance.
		Robot robot = new Robot();

		// get the time step of the current world.
		int timeStep = (int) Math.round(robot.getBasicTimeStep());

		Motor leftMotor = robot.getMotor("left wheel motor");
		Motor rightMotor = robot.getMotor("right wheel motor");
		
		DistanceSensor[] ds = new DistanceSensor[8];
		for (int i = 0; i < 8; i++)
		{
			ds[i] = robot.getDistanceSensor("ds" + i);
			ds[i].enable(timeStep);
		}

		leftMotor.setPosition(Double.POSITIVE_INFINITY);
		rightMotor.setPosition(Double.POSITIVE_INFINITY);

		// initialize devices
		Keyboard keyboard = new Keyboard();
		keyboard.enable(timeStep);
		GPS gps = new GPS("gps");
		gps.enable(timeStep);
		Compass compass = new Compass("compass");
		compass.enable(timeStep);

		final Point SRC_POINT = points.get(0);
		final Point TAR_POINT = points.get(points.size() - 1);  
		Point curTarget = new Point(TAR_POINT.x, TAR_POINT.z);

		while (robot.step(timeStep) != -1)
		{
			int keyCode = keyboard.getKey();
			double leftSpeed = 0.0, rightSpeed = 0.0;
			if(keyCode == 'C')
			{
				double[] compass_values = compass.getValues();
				System.out.format("Using the Compass device: %.3f %.3f %.3f\n", compass_values[0], compass_values[1],
						compass_values[2]);
			}
			else if(keyCode == 'G')
			{
				double[] gps_values = gps.getValues();
				System.out.format("Using the GPS device: %.3f %.3f %.3f\n", gps_values[0], gps_values[1],
						gps_values[2]);
			}
			else if(keyCode == Keyboard.HOME)
			{
				handControl = true;
			}
			else if(keyCode == Keyboard.END)
			{
				handControl = false;
			}
			if(handControl)
			{
				if(keyCode == Keyboard.UP)
				{
					leftSpeed = rightSpeed = MAX_SPEED;
				}
				else if(keyCode == Keyboard.DOWN)
				{
					leftSpeed = rightSpeed = -MAX_SPEED;
				}
				else if(keyCode == Keyboard.LEFT)
				{
					leftSpeed -= 0.2 * MAX_SPEED;
					rightSpeed += 0.2 * MAX_SPEED;
				}
				else if(keyCode == Keyboard.RIGHT)
				{
					leftSpeed += 0.2 * MAX_SPEED;
					rightSpeed -= 0.2 * MAX_SPEED;
				}
			}
			else
			{
				double[] gps_values = gps.getValues();
				double curX = gps_values[0];
				double curZ = gps_values[2];
				final Point targetVec = new Point(TAR_POINT.x - curX, TAR_POINT.z - curZ);
				
//				System.out.println(TAR_POINT.x + "," +  TAR_POINT.z + "," + curX + "," + curZ);
				System.out.println(targetVec.getLength());
				if(targetVec.getLength() >= 0.1)
				{
					
					double[] dsValues = {0, 0, 0, 0, 0, 0, 0, 0};
					for (int i = 0; i < 8; i++)
					{
						dsValues[i] = ds[i].getValue();
					}
					
					// detect obstacles
					boolean left_obstacle = dsValues[7] > DS_VALUE;
					boolean right_obstacle = dsValues[0] > DS_VALUE;
					
					if(left_obstacle)
					{
						//turn right
						leftSpeed += 0.2 * MAX_SPEED;
						rightSpeed -= 0.2 * MAX_SPEED;
						meetObstacle = true;
						
					}
					else if(right_obstacle)
					{
						//turn left
						leftSpeed -= 0.2 * MAX_SPEED;
						rightSpeed += 0.2 * MAX_SPEED;
						meetObstacle = true;
					}
					else
					{
						
						if(meetObstacle)
						{
							meetObstacle = false;
							double goTowardTar = random.nextDouble();
							double coeX = random.nextDouble();
							double coeZ = random.nextDouble();
							double newX = 0.0;
							double newZ = 0.0;
							if(goTowardTar <= 0.2)
							{
								double augX = 2 * curX - TAR_POINT.x;
								double augZ = 2 * curZ - TAR_POINT.z;
								newX = coeX * augX + (1 - coeX) * TAR_POINT.x;
								newZ = coeZ * augZ + (1 - coeZ) * TAR_POINT.z;
							}
							else
							{
								newX = coeX * curX + (1 - coeX) * TAR_POINT.x;
								newZ = coeZ * curZ + (1 - coeZ) * TAR_POINT.z;
							}
							curTarget.x = newX;
							curTarget.z = newZ;
							
							
							
						}

						Point moveVec = new Point(curTarget.x - curX, curTarget.z - curZ);
//						System.out.println(curTarget.x + "," + curTarget.z);
						if(moveVec.getLength() < 0.05)
						{
							double coeX = random.nextDouble();
							double coeZ = random.nextDouble();
							double newX = coeX * curX + (1 - coeX) * TAR_POINT.x;
							double newZ = coeZ * curZ + (1 - coeZ) * TAR_POINT.z;
							curTarget.x = newX;
							curTarget.z = newZ;
							moveVec = new Point(curTarget.x - curX, curTarget.z - curZ);
						}
						else
						{
							double[] compass_values = compass.getValues();
							double comX = compass_values[0];
							double comZ = compass_values[2];
							
							moveVec.normalize();
							Point front = new Point(-comX, comZ);
							
							double beta = angle(front, moveVec) - Math.PI;
							

					
							if(beta > 0.05)
							{
								leftSpeed = MAX_SPEED * beta / Math.PI;
								rightSpeed = -MAX_SPEED * beta / Math.PI;
							}
							else if(beta < -0.05)
							{
								leftSpeed = -MAX_SPEED;
								rightSpeed = MAX_SPEED;
							}
							else
							{
								leftSpeed = MAX_SPEED - Math.PI + beta;
								rightSpeed = MAX_SPEED - Math.PI - beta;
							}
						}
					}
				}
			}
			leftMotor.setVelocity(leftSpeed);
			rightMotor.setVelocity(rightSpeed);
		}

	}
}
