// Movement utilities
void rotate1w (int deg) {
     if (deg >= 0)
          RotateMotorPID(OUT_DRIVE_R, 100, deg * MM2DEG(PI * TRACK_FRONT_MM) / 180, PID_P, PID_I, PID_D);
     else
          RotateMotorPID(OUT_DRIVE_L, 100, -deg * MM2DEG(PI * TRACK_FRONT_MM) / 180, PID_P, PID_I, PID_D);
     ResetAllTachoCounts(OUT_DRIVE);
     Wait(10);
}

void rotate2w (int deg) {
     byte outputs[2] = {OUT_DRIVE_L, OUT_DRIVE_R};
     if (deg >= 0)
        RotateMotorExPID(outputs, 100, deg * MM2DEG(PI * TRACK_FRONT_MM) / 360, 100, true, true, PID_P, PID_I, PID_D);
     else
         RotateMotorExPID(outputs, 100, -deg * MM2DEG(PI * TRACK_FRONT_MM) / 360, -100, true, true, PID_P, PID_I, PID_D);
     ResetAllTachoCounts(OUT_DRIVE);
     Wait(10);
}

void run (int mm) {
  byte outputs[2] = {OUT_DRIVE_L, OUT_DRIVE_R};
  RotateMotorExPID(outputs, 100, MM2DEG(mm), 0, true, true, PID_P, PID_I, PID_D);
  myPos.x += sin256(myPos.heading) * mm / 256;
  myPos.y += sin256(myPos.heading + 90) * mm / 256;
}

void kick () {
	RotateMotorPID(OUT_KICK, 100, -90, PID_P, PID_I, PID_D);
	RotateMotorPID(OUT_KICK, 100, 90, PID_P, PID_I, PID_D);
}

void MOV_init() {
	ResetAllTachoCounts(OUT_KICK);
	Wait(10);
}

