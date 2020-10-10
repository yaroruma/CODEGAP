#ifndef EXAM_CV_H_
#define EXAM_CV_H_ 

#ifdef __cplusplus
extern "C" {
#endif

void vertical_parking(void);
void horizental_parking(void);
short start_signal(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf, int nw, int nh);
void trace_color(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf, int nw, int nh);
void rotate_tracing(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf);
void tunnel_right(int d1,int d2);
int line_tracing(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf);
int line_tracing2(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf);
int detect_traffic_light(unsigned char* srcBuf, int iw, int ih, int color_green, int ranges, int saturation_th3, int value_th3, unsigned char* outBuf);
int detect_sudden_stop(unsigned char* srcBuf, int iw, int ih, int color_red1, int ranges, int saturation_th1, int value_th1, unsigned char* outBuf);
int choowol(unsigned char* srcBuf, int iw, int ih, unsigned char* outBuf);

#ifdef __cplusplus
}
#endif

#endif //EXAM_CV_H_

