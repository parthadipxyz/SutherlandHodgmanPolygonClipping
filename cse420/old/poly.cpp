
#include<iostream>
#include <fstream>
#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
using namespace std;
int can=0;
float Xmin,Xmax,Ymin,Ymax;
float vc1[20][2];
float vc2[20][2];
//int start_seq=1;
int curr_vert_num=0;
int next_index=0,c_index=0,out_index=0;

void display() {

  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);

  // Drawing is done by specifying a sequence of vertices.  The way these
  // vertices are connected (or not connected) depends on the argument to
  // glBegin.  GL_POLYGON constructs a filled polygon.
  glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 1, 0);
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}






float slope(float x0,float y0,float x1,float y1)
{   float slope;
    if(x1 != x0)
       slope=(y1-y0)/(x1-x0);
    else slope=101;
    return slope;
}

float print_seq_ready_next(int vert_num){
    int j=0;

        while(j<curr_vert_num){

         vc1[j][0]=vc2[j][0];
         vc1[j][1]=vc2[j][1];


          cout<<"("<<vc2[j][0]<<", "<<vc2[j][1]<<") ";

        j++;
        }

   ////////////////////////////


  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(400, 300);
  glutCreateWindow("A Simple Triangle");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  //glutDisplayFunc(display);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.
  //glutMainLoop();





   /////////////////////////////

    next_index=0;
    c_index=0;
    out_index=0;
    cout<<endl;


}


float clip(string edge)
{
    int work_vert_num=curr_vert_num,i=0;
    float m,c,x0,y0,x1,y1;

    if(edge=="L")
    {
        cout<<"Clipping with respect to LEFT edge..."<<endl<<"New Sequence : ";


        while(i<work_vert_num)
        {

            if(c_index == work_vert_num-1)
            {
                next_index=0;

            }
            else
                next_index=c_index+1;

            x0=vc1[c_index][0];
            y0=vc1[c_index][1];
            x1=vc1[next_index][0];
            y1=vc1[next_index][1];


            if(x0<Xmin && x1>Xmin)
            {
                //out to in
                //cout<<"out-in";

                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmin;
                vc2[out_index][1]= m*Xmin+c;
                vc2[out_index+1][0]=x1;
                vc2[out_index+1][1]=y1;

                out_index=out_index+2;
            }
            else if(x0>=Xmin && x1<Xmin)
            {
                 //cout<<"in-out";
                //in to out
                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmin;
                vc2[out_index][1]= m*Xmin+c;

                out_index++;
            }
            else if(x1>=Xmin && x0 >= Xmin)
            {
               //cout<<"out-in";
                //in-in
                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }


            c_index++;
            i++;
        }


        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num);


    }

    else if(edge=="R")
    {
        cout<<endl<<"Clipping with respect to RIGHT edge..."<<endl<<"New Sequence : ";
        while(i<work_vert_num)
            {

            if(c_index == work_vert_num-1)
            {
                next_index=0;
                //cout<<"Hi";
            }
            else
                next_index=c_index+1;

            x0=vc1[c_index][0];
            y0=vc1[c_index][1];
            x1=vc1[next_index][0];
            y1=vc1[next_index][1];


            if(x0>Xmax && x1<Xmax)
            {
                //out to in
                //cout<<"out-in";

                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmax;
                vc2[out_index][1]= m*Xmax+c;
                vc2[out_index+1][0]=x1;
                vc2[out_index+1][1]=y1;
                out_index=out_index+2;
            }
            else if(x0<=Xmax && x1>Xmax)
            {
                 //cout<<"in-out";
                //in to out
                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmax;
                vc2[out_index][1]= m*Xmax+c;

                out_index++;
            }

            else if(x0<=Xmax && x1<=Xmax)
            {
               //in to in

                vc2[out_index][0]=x1;
                vc2[out_index][1]=y1;

                out_index++;



            }

            c_index++;
            i++;
        }


        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num);



    }
    else if(edge=="B")
    {
       cout<<endl<<"Clipping with respect to BOTTOM edge..."<<endl<<"New Sequence : ";

        while(i<work_vert_num)
        {

            if(c_index == work_vert_num-1)
            {
                next_index=0;
                //cout<<"Hi";
            }
            else
                next_index=c_index+1;

            x0=vc1[c_index][0];
            y0=vc1[c_index][1];
            x1=vc1[next_index][0];
            y1=vc1[next_index][1];

            if(y0<Ymin && y1>Ymin)
            {
                //out to in
                //cout<<"out-in";

                m=slope(x0,y0,x1,y1);

                c=y0-m*x0;
                if(m!=101)
                 vc2[out_index][0]=(Ymin-c)/m;
                else vc2[out_index][0]=x0;
                vc2[out_index][1]= Ymin;
                vc2[out_index+1][0]=x1;
                vc2[out_index+1][1]=y1;

                out_index=out_index+2;
            }
            else if(y0>=Ymin && y1<Ymin)
            {
                 //cout<<"in-out";
                //in to out
                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;
                if(m !=101)
                    vc2[out_index][0]=(Ymin-c)/m;
                else vc2[out_index][0]=x1;

                vc2[out_index][1]= Ymin;
                out_index++;
            }
            else if(y0>=Ymin && y1>=Ymin )
            {
               //cout<<"out-in";
                //in-in
                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;
                out_index++;

            }

            c_index++;
            i++;
        }



        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num);



    }
    else
    {     cout<<endl<<"Clipping with respect to TOP edge..."<<endl<<"New Sequence : ";

        while(i<work_vert_num)
        {

            if(c_index == work_vert_num-1)
            {
                next_index=0;
                //cout<<"Hi";
            }
            else
                next_index=c_index+1;

            x0=vc1[c_index][0];
            y0=vc1[c_index][1];
            x1=vc1[next_index][0];
            y1=vc1[next_index][1];

            if(y0>Ymax && y1<Ymax)
            {
                //out to in
                //cout<<"out-in";

                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;
                if(m !=101)
                 vc2[out_index][0]=(Ymax-c)/m;
                else  vc2[out_index][0]=x0;
                vc2[out_index][1]= Ymax;
                vc2[out_index+1][0]=x1;
                vc2[out_index+1][1]=y1;
                out_index=out_index+2;
            }
            else if(y0<=Ymax && y1>Ymax)
            {
                 //cout<<"in-out";
                //in to out
                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;
                if(m!=101)
                vc2[out_index][0]=(Ymax-c)/m;
                else vc2[out_index][1]= x1;

                vc2[out_index][1]= Ymax;
                out_index++;
            }
            else if(y0<=Ymax &&  y1 <= Ymax  )
            {
               //cout<<"in-in";
                //in-in
                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }

            c_index++;
            i++;
        }



        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num);

    }




}

int main()
{





    string order[4];
    int vert_num;


    ifstream file;
    file.open("in.txt");

    if (!file)
        cout << "Unable to open file";



    file >> Xmin;
    file >> Xmax;
    file >> Ymin;
    file >> Ymax;
    file >> order[0];
    file >> order[1];
    file >> order[2];
    file >> order[3];
    file >> vert_num;

    cout<<"Xmin = "<<Xmin<<endl;
    cout<<"Xmax = "<<Xmax<<endl;
    cout<<"Ymin = "<<Ymin<<endl;
    cout<<"Ymax = "<<Ymax<<endl;
    cout<<"Clipping edge sequence: "<<order[0]<<" "<<order[1]<<" "<<order[2]<<" "<<order[3]<<endl;
    cout<<"No. of vertices in the polygon = "<<vert_num<<endl;

    int i=0;

    while(i<vert_num)
    {
        file>>vc1[i][0];
        file>>vc1[i][1];
        cout<<"P"<<i+1<<" : "<<"("<<vc1[i][0]<<", "<<vc1[i][1]<<")"<<endl;
        i++;
    }
    cout<<endl;
    //cout<<vc1[2][1];
    curr_vert_num=vert_num;

    for(int i=0; i<4; i++)
    {


        clip(order[i]);
        //cout<<endl;

    }

   cout<<endl<<endl<<endl;

   cout<<"PRESS ANY KEY TO EXIT..."<<endl;
    getchar();
}


