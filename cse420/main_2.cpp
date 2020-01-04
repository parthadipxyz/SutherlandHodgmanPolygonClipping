
#include<iostream>
#include <fstream>
#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>


using namespace std;
//int can=0;

float Xmin,Xmax,Ymin,Ymax,vc1[20][2],vc2[20][2],inp[20][2],out_b[20][2],out_l[20][2],out_r[20][2],out_t[20][2],w=400,h=400;
int vert_num,l_s=0,b_s=0,t_s=0,r_s=0,curr_vert_num=0,next_index=0,c_index=0,out_index=0;

//string dis;
float norm(float num){

int scale=400;
return (num-(-scale))/(scale-(-scale))*2+(-1);

}

void dis_comm(){
float b,t,l,r;

l=norm(Xmin);
r=norm(Xmax);
b=norm(Ymin);
t=norm(Ymax);

glLineWidth(2);
glColor3f(1, 1, 1);

// clip rectangle
glBegin(GL_LINES);

  glVertex2f(l, 1);
  glVertex2f(l, -1);

  glVertex2f(r, 1);
  glVertex2f(r, -1);

  glVertex2f(1, b);
  glVertex2f(-1, b);

  glVertex2f(1, t);
  glVertex2f(-1, t);
glEnd();

glBegin(GL_LINE_LOOP);
    int j=0;
    float t1,t2;
    //float ex1,ex2;

    while(j<vert_num){

        t1=norm(inp[j][0]);
        t2=norm(inp[j][1]);

        glColor3f(1,1,1);
        glVertex3f(t1, t2, 0);

     j++;
    }

  glEnd();

}

void out_data_import(float *p,int siz){
    //cout<<siz;
//float *bak;
//bak=p;
//p++;
dis_comm();

glBegin(GL_LINE_LOOP);
//glBegin(GL_POLYGON);
    int j=0;
    float t1,t2;
    cout<<endl;
    while(j<siz){

        t1=norm(*p);
        //cout<<*p;
        p++;
        //cout<<","<<*p<<endl;
        t2=norm(*p);
        p++;

        //cout<<endl<<t2<<endl;
        //polygon color
        glColor3f(1,0,0);
        glVertex3f(t1, t2,0);


     j++;
     //if(j==siz) p=bak;
    }

  glEnd();
  glutSwapBuffers ();
  glFlush();




}

void display_l() {
    out_data_import(&out_l[0][0],l_s);
}
void display_t() {
    out_data_import(&out_t[0][0],t_s);

}
void display_r() {

 out_data_import(&out_r[0][0],r_s);

}
void display_b() {
out_data_import(&out_b[0][0],b_s);
}

void glinit(string frame_name,int y){
  //int argc;
  //char** argv;
  //glutInit(&argc, argv);
  //
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  // Position window at (80,80)-(480,380) and give it a title.
  if(y==0)
  glutInitWindowPosition(0, 0);
  else if(y==1)
  glutInitWindowPosition(w, 0);
  else if(y==2)
  glutInitWindowPosition(0, w);
  else if(y==3)
  glutInitWindowPosition(w, w);

  glutInitWindowSize(w, h);

  if(frame_name=="L")
  {glutCreateWindow("Left");
  //dis="L";
  glutDisplayFunc(display_l);
  }

  //display();
  else if(frame_name=="R")
  {glutCreateWindow("Right");
  glutDisplayFunc(display_r);
  }

  else if(frame_name=="T")
  {glutCreateWindow("Top");
  //dis="T";
   glutDisplayFunc(display_t);
  }

  else if(frame_name=="B")
  {glutCreateWindow("Bottom");
  //dis="B";
  glutDisplayFunc(display_b);

  }



}

float slope(float x0,float y0,float x1,float y1)
{   float slope;
    if(x1 != x0)
       slope=(y1-y0)/(x1-x0);
    else slope=101;
    return slope;
}

void print_seq_ready_next(int vert_num,string edge_name){
    int j=0;
    //float *ptr;


        while(j<curr_vert_num){

            vc1[j][0]=vc2[j][0];
            vc1[j][1]=vc2[j][1];
            //out_t[j][1] = vc2[j][1];


            if(edge_name=="L"){
            out_l[j][0]=vc2[j][0];
            out_l[j][1]=vc2[j][1];
            l_s++;
            }

            else if(edge_name=="R"){
            out_r[j][0]=vc2[j][0];
            out_r[j][1]=vc2[j][1];
            r_s++;

            }
           else if(edge_name=="T"){
            out_t[j][0] = vc2[j][0];
            out_t[j][1] = vc2[j][1];
              t_s++;
            }
            else if(edge_name=="B"){
                out_b[j][0]=vc2[j][0];
                out_b[j][1]=vc2[j][1];
                b_s++;
            }


          cout<<"("<<vc2[j][0]<<", "<<vc2[j][1]<<") ";

        j++;
        }




    next_index=0;
    c_index=0;
    out_index=0;

    cout<<endl;


}


void clip(string edge)
{
    int work_vert_num=curr_vert_num,i=0;
    float m,c,x0,y0,x1,y1;

    if(edge=="L")
    {
        cout<<"Clipping with respect to LEFT edge..."<<endl<<"New Sequence : ";


        while(i<work_vert_num)
        {
            //index rotation after first index
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


                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmin;
                vc2[out_index][1]= m*Xmin+c;
                vc2[out_index+1][0]=x1;
                vc2[out_index+1][1]=y1;

                out_index=out_index+2;
            }
            else if(x0>Xmin && x1<Xmin)
            {

                //in to out
                m=slope(x0,y0,x1,y1);
                c=y0-m*x0;

                vc2[out_index][0]=Xmin;
                vc2[out_index][1]= m*Xmin+c;

                out_index++;
            }
            else if(x1>=Xmin && x0 >= Xmin)//
            {

                //in-in
                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }
            else if( x0 < Xmin && x1== Xmin )//stops two vertice register
            {
               //out to in just touched;

                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }
            else if(x0==Xmin && x1<Xmin){
            //goes out from edge


            }


            c_index++;
            i++;
        }


        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num,edge);


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
            else if(x0<Xmax && x1>Xmax)
            {

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
            else if(x0>Xmax && x1==Xmax)
            {
               //out in just touch

                vc2[out_index][0]=x1;
                vc2[out_index][1]=y1;

                out_index++;



            }
            else if(x0 == Xmax && x1>Xmax)
            {
               //goes out from edge

                //do nothing
            //cout<<"jj";


            }

            c_index++;
            i++;
        }


        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num,edge);



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
            else if(y0>Ymin && y1<Ymin)
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
             else if( x0 > Xmax && x1== Xmax )//
            {
               //out to in just touched;

                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }
            else if(y0==Ymin && y1<Ymin){

                //goes out from edge


            }

            c_index++;
            i++;
        }



        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num,edge);



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
            else if(y0<Ymax && y1>Ymax)
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

            else if(y0 > Ymax &&  y1 == Ymax  )
            {
               //out in just touch
                vc2[out_index][0]=x1;
                vc2[out_index][1]= y1;

                out_index++;

            }
            else if(y0 == Ymax && y1>Ymax){

             //out from edge



            }

            c_index++;
            i++;
        }



        curr_vert_num=out_index;
        print_seq_ready_next(curr_vert_num,edge);

    }




}

//using namespace std;

int main() {

    //string array for clipping order input
    string order[4];

    //file file
    ifstream file;
    file.open("C:/Users/Partha\ Dip/Desktop/ALL/cse420/in.txt");

    if (file)
        cout << "File Opened Successfully..."<<endl;
    else return -1;
    //just read things

    file >> Xmin;
    file >> Xmax;
    file >> Ymin;
    file >> Ymax;
    file >> order[0];
    file >> order[1];
    file >> order[2];
    file >> order[3];
    file >> vert_num; //number of vertices given in input file
    //print print
    cout<<"Xmin = "<<Xmin<<endl;
    cout<<"Xmax = "<<Xmax<<endl;
    cout<<"Ymin = "<<Ymin<<endl;
    cout<<"Ymax = "<<Ymax<<endl;
    cout<<"Clipping edge sequence: "<<order[0]<<" "<<order[1]<<" "<<order[2]<<" "<<order[3]<<endl;
    cout<<"No. of vertices in the polygon = "<<vert_num<<endl;

    int i=0;
    //take input verices in 2d array  index 0= x index1=y
    while(i<vert_num)
    {
        file>>vc1[i][0];
        file>>vc1[i][1];
        inp[i][0]=vc1[i][0];
        inp[i][1]=vc1[i][1];
        cout<<"P"<<i+1<<" : "<<"("<<vc1[i][0]<<", "<<vc1[i][1]<<")"<<endl;//print
        i++;
    }
    cout<<endl;
    //cout<<vc1[2][1];
    curr_vert_num=vert_num;

    for(int i=0; i<4; i++)
    {

        //This will call the function that will start and end clipping
        clip(order[i]);
        //cout<<endl;

    }

   cout<<endl<<endl<<endl;
  //cout<<l_s;
int y=0;
while(y<4){
   glinit(order[y],y);//initial setup thing windows position bla bla bla
   y++;
}






   glutMainLoop();//shows all graph after ready






   //glutMainLoop();
   cout<<"PRESS ANY KEY TO EXIT..."<<endl;




   getchar();//wait wait




}

