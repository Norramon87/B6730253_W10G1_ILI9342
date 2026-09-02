#include "event.h"
#include <Arduino.h>

lv_chart_series_t *adc_chart_data33;
lv_chart_series_t *adc_chart_data34;

void init_adc_33_34_chart()
{
int pointcount = 50;
  int min_value = 0;
  int max_value = 4095;
  // Set type of the chart
  lv_chart_set_type(objects.adc_33_34_chart, LV_CHART_TYPE_LINE);
  // Set the number of points on the chart
  lv_chart_set_point_count(objects.adc_33_34_chart, pointcount);
  // Set the range of the Y axis
  lv_chart_set_range(objects.adc_33_34_chart, LV_CHART_AXIS_PRIMARY_Y, min_value, max_value);
  // Create a data series for the chart
  adc_chart_data33 = lv_chart_add_series(objects.adc_33_34_chart, lv_color_hex(0x000080), LV_CHART_AXIS_PRIMARY_Y);
  adc_chart_data34 = lv_chart_add_series(objects.adc_33_34_chart, lv_color_hex(0xff5400), LV_CHART_AXIS_PRIMARY_Y);
}
void update_chart_adc_33_34(lv_timer_t *timer)
{
 LV_UNUSED(timer);
 lv_chart_set_next_value(objects.adc_33_34_chart,adc_chart_data33,analogRead(33));
 lv_chart_set_next_value(objects.adc_33_34_chart,adc_chart_data34,analogRead(34));
}
void event_handler(lv_event_t *e)
{
  lv_event_code_t code =lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  int *pLED1= (int *)lv_event_get_user_data(e);

  if(obj == objects.nextpage_bt && code == LV_EVENT_CLICKED)
  {
    lv_scr_load(objects.control_page);
  }
  else if(obj == objects.home_bt && code == LV_EVENT_CLICKED )
  {
    lv_scr_load(objects.main);
  }
  else if (obj == objects.onmotor_bt && code == LV_EVENT_CLICKED)
  {
    gpio_set_level((gpio_num_t)*pLED1 ,1);
  }
  else if (obj == objects.offmotor_bt && code == LV_EVENT_CLICKED)
  {
    gpio_set_level((gpio_num_t)*pLED1 ,0);
  }
  else if(obj == objects.incrementpwm && code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_increment(objects.pwmval);
  }
  else if(obj == objects.decrementpwm && code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    lv_spinbox_decrement(objects.pwmval);
  }
  else if (obj == objects. onpwm_sw)
  {
    if(lv_obj_has_state(objects.onpwm_sw,LV_STATE_CHECKED))
    {
      int pwmval_ctrl =lv_spinbox_get_value(objects.pwmval);
      analogWrite(22,pwmval_ctrl);
      Serial.printf("PWMVAL: ");
      Serial.println(pwmval_ctrl);
    }
    else 
    {
      analogWrite(22,0);
    }
    
  }
}
void led_fan(lv_timer_t*timer)
{
  int *pSW =(int*)timer->user_data;
  int status =digitalRead(*pSW);
  if(status== LOW)
  {
    lv_led_on(objects.fan_led);
  }
  else if(status== HIGH)
  {
    lv_led_off(objects.fan_led);
  }
}