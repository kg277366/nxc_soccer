// Movement utilities

typedef struct {
       long l, r;
       int h;
} RunsBegin;

RunsBegin runs_begin;

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
  myPos.y -= sin256(myPos.heading + 90) * mm / 256;
}

void runI (int speed) {
     byte outputs[2] = {OUT_DRIVE_L, OUT_DRIVE_R};
     runs_begin.l = MotorTachoCount(OUT_DRIVE_L);
     runs_begin.r = MotorTachoCount(OUT_DRIVE_R);
     runs_begin.h = myPos.heading;

     OnFwdSync(outputs, speed, 0);
}

void stopI () {
     byte outputs[2] = {OUT_DRIVE_L, OUT_DRIVE_R};
     Off(outputs);
     long l = MotorTachoCount(OUT_DRIVE_L);
     long r = MotorTachoCount(OUT_DRIVE_R);
     int d = (l + r - runs_begin.l - runs_begin.r) / 2;
     d = DEG2MM(d);

  myPos.x += sin256(runs_begin.h) * d / 256;
  myPos.y -= sin256(runs_begin.h + 90) * d / 256;
     

}

void kick () {
	OnRev(OUT_KICK, 100);
	Wait(200);
	Off(OUT_KICK);
	RotateMotorPID(OUT_KICK, 100, - MotorTachoCount(OUT_KICK), PID_P, PID_I, PID_D);
}

void MOV_init() {
  OnFwd(OUT_KICK, 40);
  Wait(1000);
	ResetAllTachoCounts(OUT_KICK);
	Wait(10);
  Off(OUT_KICK);
}

