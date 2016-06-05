package com.example.alexey.cameratrackingapp;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

// libraries
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import java.io.IOException;
import static android.graphics.Color.blue;
import static android.graphics.Color.green;
import static android.graphics.Color.red;
import static android.graphics.Color.rgb;

public class MainActivity extends Activity implements TextureView.SurfaceTextureListener {
    private Camera      mCamera;
    private TextureView mTextureView;
    private SurfaceView mSurfaceView;
    private SurfaceHolder mSurfaceHolder;
    private Bitmap      bmp = Bitmap.createBitmap(640,480,Bitmap.Config.ARGB_8888);
    private Canvas      canvas = new Canvas(bmp);
    private Paint       paint1 = new Paint();
    private TextView    mTextView;
    private SeekBar     myControl1;
    private SeekBar     myControl2;
    private SeekBar     myControl3;
    private TextView    myTextView1;
    private TextView    myTextView2;
    private TextView    myTextView3;
    private ImageButton btnSwitch;
    private boolean     isFlashOn;
    Parameters params;


    static long prevtime = 0; // for FPS calculation

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); // keeps the screen from turning off

        mSurfaceView = (SurfaceView) findViewById(R.id.surfaceview);
        mSurfaceHolder = mSurfaceView.getHolder();

        mTextureView = (TextureView) findViewById(R.id.textureview);
        mTextureView.setSurfaceTextureListener(this);

        mTextView = (TextView) findViewById(R.id.cameraStatus);
        //
        myControl1 = (SeekBar) findViewById(R.id.seek1);
        myTextView1 = (TextView) findViewById(R.id.textView01);
        myTextView1.setText("R  : "+myControl1.getProgress());
        //
        myControl2 = (SeekBar) findViewById(R.id.seek2);
        myTextView2 = (TextView) findViewById(R.id.textView02);
        myTextView2.setText("RG  : "+myControl2.getProgress());
        //
        myControl3 = (SeekBar) findViewById(R.id.seek3);
        myTextView3 = (TextView) findViewById(R.id.textView03);
        myTextView3.setText("RB: " + myControl3.getProgress());
        //
        paint1.setColor(0xffff0000); // red
        paint1.setTextSize(24);
        setMyControlListener1();
        setMyControlListener2();
        setMyControlListener3();
        btnSwitch = (ImageButton)findViewById(R.id.btnSwitch);
        btnSwitch.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (isFlashOn) {
                    // turn off flash
                    turnOffFlash();
                } else {
                    // turn on flash
                    turnOnFlash();
                }
            }
        });
    }

    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        mCamera = Camera.open();
        Camera.Parameters parameters = mCamera.getParameters();
        parameters.setPreviewSize(640, 480);
        //parameters.setColorEffect(Camera.Parameters.EFFECT_MONO); // black and white
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_INFINITY); // no autofocusing
        parameters.setAutoWhiteBalanceLock(true);
        //parameters.setFlashMode(Camera.Parameters.FLASH_MODE_TORCH);
        mCamera.setParameters(parameters);
        mCamera.setDisplayOrientation(90); // rotate to portrait mode

        try {
            mCamera.setPreviewTexture(surface);
            mCamera.startPreview();
        } catch (IOException ioe) {
            // Something bad happened
        }
    }

    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        // Ignored, Camera does all the work for us
    }

    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        mCamera.stopPreview();
        mCamera.release();
        return true;
    }

    // the important function
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        // Invoked every time there's a new Camera preview frame
        mTextureView.getBitmap(bmp);

        final Canvas c = mSurfaceHolder.lockCanvas();
        if (c != null) {
            int rthresh = myControl1.getProgress();
            int gthresh = myControl3.getProgress();
            int bthresh = myControl2.getProgress();
            int[] pixels1 = new int[bmp.getWidth()];
            int[] pixels2 = new int[bmp.getWidth()];
            int[] pixels3 = new int[bmp.getWidth()];
            int startY1 = 120; // which row in the bitmap to read
            int startY2 = 240;
            int startY3 = 360;
            // only look at one row in the image
            bmp.getPixels(pixels1, 0, bmp.getWidth(), 0, startY1, bmp.getWidth(), 1); // (array name, offset inside array, stride (size of row), start x, start y, num pixels to read per row, num rows to read)
            bmp.getPixels(pixels2, 0, bmp.getWidth(), 0, startY2, bmp.getWidth(), 1); // (array name, offset inside array, stride (size of row), start x, start y, num pixels to read per row, num rows to read)
            bmp.getPixels(pixels3, 0, bmp.getWidth(), 0, startY3, bmp.getWidth(), 1); // (array name, offset inside array, stride (size of row), start x, start y, num pixels to read per row, num rows to read)
            // pixels[] is the RGBA data (in black an white).
            // instead of doing center of mass on it, decide if each pixel is dark enough to consider black or white
            // then do a center of mass on the thresholded array
            int[] thresholdedPixels1 = new int[bmp.getWidth()];
            int[] thresholdedPixels2 = new int[bmp.getWidth()];
            int[] thresholdedPixels3 = new int[bmp.getWidth()];
            int[] thresholdedColors1 = new int[bmp.getWidth()];
            int[] thresholdedColors2 = new int[bmp.getWidth()];
            int[] thresholdedColors3 = new int[bmp.getWidth()];
            int wbTotal1 = 0; // total mass
            int wbTotal2 = 0; // total mass
            int wbTotal3 = 0; // total mass
            int wbCOM1 = 0; // total (mass time position)
            int wbCOM2 = 0; // total (mass time position)
            int wbCOM3 = 0; // total (mass time position)
            for (int i = 0; i < bmp.getWidth(); i++) {
                // sum the red, green and blue, subtract from 255 to get the darkness of the pixel.
                // if it is greater than some value (600 here), consider it black
                // play with the 600 value if you are having issues reliably seeing the line
                //if (((red(pixels1[i])>rthresh)&&(blue(pixels1[i])<bthresh)&&(green(pixels1[i])<gthresh))) {
                if ((red(pixels1[i])>rthresh)&&((255-(green(pixels1[i])-red(pixels1[i])) > gthresh))&&((255-(blue(pixels1[i])-red(pixels1[i])) > bthresh))){
                    thresholdedPixels1[i] = 255*3;
                    thresholdedColors1[i] = rgb(255,0,0);
                }
                else {
                    thresholdedPixels1[i] = 0;
                    thresholdedColors1[i] = rgb(0,255,0);
                }
                wbTotal1 = wbTotal1 + thresholdedPixels1[i];
                wbCOM1 = wbCOM1 + thresholdedPixels1[i]*i;
                // sum the red, green and blue, subtract from 255 to get the darkness of the pixel.
                // if it is greater than some value (600 here), consider it black
                // play with the 600 value if you are having issues reliably seeing the line
                //if ((red(pixels2[i])>rthresh)&&(blue(pixels2[i])<bthresh)&&(green(pixels2[i])<gthresh)) {
                if ((red(pixels2[i])>rthresh)&&((255-(green(pixels2[i])-red(pixels2[i])) > gthresh))&&((255-(blue(pixels2[i])-red(pixels2[i])) > bthresh))){
                    thresholdedPixels2[i] = 255*3;
                    thresholdedColors2[i] = rgb(255,0,0);
                }
                else {
                    thresholdedPixels2[i] = 0;
                    thresholdedColors2[i] = rgb(0,255,0);
                }
                wbTotal2 = wbTotal2 + thresholdedPixels2[i];
                wbCOM2 = wbCOM2 + thresholdedPixels2[i]*i;
                // sum the red, green and blue, subtract from 255 to get the darkness of the pixel.
                // if it is greater than some value (600 here), consider it black
                // play with the 600 value if you are having issues reliably seeing the line
                //if ((red(pixels3[i])>rthresh)&&(blue(pixels3[i])<bthresh)&&(green(pixels3[i])<gthresh)) {
                if ((red(pixels3[i])>rthresh)&&((255-(green(pixels3[i])-red(pixels3[i])) > gthresh))&&((255-(blue(pixels3[i])-red(pixels3[i])) > bthresh))){
                    thresholdedPixels3[i] = 255*3;
                    thresholdedColors3[i] = rgb(255, 0, 0);
                }
                else {
                    thresholdedPixels3[i] = 0;
                    thresholdedColors3[i] = rgb(0, 255, 0);
                }
                wbTotal3 = wbTotal3 + thresholdedPixels3[i];
                wbCOM3 = wbCOM3 + thresholdedPixels3[i]*i;
            }
            int COM1;
            int COM2;
            int COM3;
            //watch out for divide by 0
            if (wbTotal1<=0) {
                COM1 = bmp.getWidth()/2;
            }
            else {
                COM1 = wbCOM1/wbTotal1;
            }
            if (wbTotal2<=0) {
                COM2 = bmp.getWidth()/2;
            }
            else {
                COM2 = wbCOM2/wbTotal2;
            }
            if (wbTotal3<=0) {
                COM3 = bmp.getWidth()/2;
            }
            else {
                COM3 = wbCOM3/wbTotal3;
            }

            // draw a circle where you think the COM is
            canvas.drawCircle(COM1, startY1, 5, paint1);
            canvas.drawCircle(COM2, startY2, 5, paint1);
            canvas.drawCircle(COM3, startY3, 5, paint1);
            bmp.setPixels(thresholdedColors1, 0, bmp.getWidth(), 0, startY1, bmp.getWidth(), 1);
            bmp.setPixels(thresholdedColors2, 0, bmp.getWidth(), 0, startY2, bmp.getWidth(), 1);
            bmp.setPixels(thresholdedColors3, 0, bmp.getWidth(), 0, startY3, bmp.getWidth(), 1);
            // also write the value as text
            canvas.drawText("COM = " + COM1, 10, startY1, paint1);
            canvas.drawText("COM = " + COM2, 10, startY2, paint1);
            canvas.drawText("COM = " + COM3, 10, startY3, paint1);
            c.drawBitmap(bmp, 0, 0, null);
            mSurfaceHolder.unlockCanvasAndPost(c);

            // calculate the FPS to see how fast the code is running
            long nowtime = System.currentTimeMillis();
            long diff = nowtime - prevtime;
            mTextView.setText("FPS " + 1000/diff);
            prevtime = nowtime;
        }
    }
    private void setMyControlListener1() {
        myControl1.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                myTextView1.setText("R  : "+progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }
    private void setMyControlListener2() {
        myControl2.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                myTextView2.setText("RG  : "+progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }
    private void setMyControlListener3() {
        myControl3.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                myTextView3.setText("RB: "+progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }
    private void turnOnFlash() {
        if (!isFlashOn) {
            params = mCamera.getParameters();
            params.setFlashMode(Parameters.FLASH_MODE_TORCH);
            mCamera.setParameters(params);
            isFlashOn = true;
        }
    }
    private void turnOffFlash() {
        if (isFlashOn) {
            params = mCamera.getParameters();
            params.setFlashMode(Parameters.FLASH_MODE_OFF);
            mCamera.setParameters(params);
            isFlashOn = false;
        }
    }
}