// Movement utilities
byte MOV_outputs[2] = {OUT_DRIVE_L, OUT_DRIVE_R};
void rotate1w (int deg) {
     if (deg > 0)
          RotateMotorPID(OUT_DRIVE_R, 100, deg * MM2DEG(PI * TRACK_FRONT_MM) / 180, PID_P, PID_I, PID_D);
     else
          RotateMotorPID(OUT_DRIVE_L, 100, -deg * MM2DEG(PI * TRACK_FRONT_MM) / 180, PID_P, PID_I, PID_D);
     ResetAllTachoCounts(MOV_outputs);
}

void rotate2w (int deg) {
     RotateMotorExPID(MOV_outputs, 100, deg * MM2DEG(PI * TRACK_FRONT_MM) / 360, 100, true, true, PID_P, PID_I, PID_D);
}

