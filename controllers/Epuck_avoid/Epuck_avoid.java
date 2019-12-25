import com.cyberbotics.webots.controller.Robot;
import com.cyberbotics.webots.controller.DistanceSensor;
import com.cyberbotics.webots.controller.Motor;

public class Epuck_avoid {

  public static void main(String[] args) {
  
    Robot robot = new Robot();
    // time in [ms] of a simulation step
    int timeStep = (int) Math.round(robot.getBasicTimeStep());

    double MAX_SPEED = 6.28;

    // create the Robot instance.


    // initialize devices
    DistanceSensor[] ps = new DistanceSensor[8];
    String[] psNames = {
      "ps0", "ps1", "ps2", "ps3",
      "ps4", "ps5", "ps6", "ps7"
    };

    for (int i = 0; i < 8; i++) {
      ps[i] = robot.getDistanceSensor(psNames[i]);
      ps[i].enable(timeStep);
    }

    Motor leftMotor = robot.getMotor("left wheel motor");
    Motor rightMotor = robot.getMotor("right wheel motor");
    leftMotor.setPosition(Double.POSITIVE_INFINITY);
    rightMotor.setPosition(Double.POSITIVE_INFINITY);
    leftMotor.setVelocity(0.0);
    rightMotor.setVelocity(0.0);


    // feedback loop: step simulation until receiving an exit event
    while (robot.step(timeStep) != -1) {
      // read sensors outputs
      double[] psValues = {0, 0, 0, 0, 0, 0, 0, 0};
      for (int i = 0; i < 8 ; i++)
        psValues[i] = ps[i].getValue();

      // detect obstacles
      boolean right_obstacle =
        psValues[0] > 70.0 ||
        psValues[1] > 70.0 ||
        psValues[2] > 70.0;
      boolean left_obstacle =
        psValues[5] > 70.0 ||
        psValues[6] > 70.0 ||
        psValues[7] > 70.0;

      // initialize motor speeds at 50% of MAX_SPEED.
      double leftSpeed  = 0.5 * MAX_SPEED;
      double rightSpeed = 0.5 * MAX_SPEED;
      // modify speeds according to obstacles
      if (left_obstacle) {
        // turn right
        leftSpeed  += 0.5 * MAX_SPEED;
        rightSpeed -= 0.5 * MAX_SPEED;
      }
      else if (right_obstacle) {
        // turn left
        leftSpeed  -= 0.5 * MAX_SPEED;
        rightSpeed += 0.5 * MAX_SPEED;
      }
      // write actuators inputs
      leftMotor.setVelocity(leftSpeed);
      rightMotor.setVelocity(rightSpeed);
    };
  }
}