using System.Collections;
using System.Collections.Generic;
using UnityEngine;

    
public class accel : MonoBehaviour
{
    public double X;
    public double Y;
    public double Z;

    public static int i;
    public static int j;
    public static int max;
    Entity_Sheet2 es;
    /*TextScript.cs内でも使用する変数であるため、グローバルな変数として宣言しておく*/
    /*各変数には加速度センサーのX、Y、Zの値が格納される*/
    public static double xValue;
    public static double yValue;
    public static double zValue;
    /*四次元数の回転を表すメンバー変数accelerationを宣言する*/
    private Quaternion acceleration;
    void Start()
    {
        es = Resources.Load("mpu1") as Entity_Sheet2;
        max = es.sheets[0].list.Count;
    }
    void Update()
    {
        /*別スレッドからAccelerometerValueメソッドを1秒ごとに呼び出す*/
        Invoke("AccelerometerValue",1.0f);
    }
    /*Update()メソッドより常に呼び出されるAccelerometerValueメソッド*/
    private void AccelerometerValue()
    {
        for (j = 0; j < 40; j++)
        {
            Debug.Log("aaa");
        }
        if (i < max-1)
        {
            i++;
        }
        double xValue = es.sheets[0].list[i].ac_x;
        double yValue = es.sheets[0].list[i].ac_y;
        double zValue = es.sheets[0].list[i].ac_z;
        
        /*float型に変換した加速度センサーの各値を指定し、その値に応じてCubeを回転させる*/
        /*引数には、X、Y、Z、Wの値が必要だが、今回Wの値は不要なので、0.0fと指定しておく*/
        acceleration.x = (float)xValue;
        acceleration.y = (float)yValue;
        acceleration.z = (float)zValue;
        transform.rotation = new Quaternion(acceleration.x, acceleration.y, acceleration.z, 0.0f);
    }
    /* I2Cバス、加速度計、およびタイマーを初期化する処理 */
    /*タイマーから呼び出されるTimerCallback()メソッド処理*/

    /*TimerCallbackから呼び出されるReadAccell()メソッド処理*/

}
