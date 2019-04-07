#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#define GOLDEN_RATIO (0.2 +1.61803398875)
using namespace std;
using namespace cv;

struct Circle{
    int x,y,r;
    Circle(){}
    Circle(int a,int b,int c){
        x=a;y=b;r=c;
    }
    Circle(Circle& B){
        x=B.x;y=B.y;r=B.r;
    }
    void output(){
        printf("This Circle has (x,y,r) = (%d, %d, %d)",x,y,r);
    }
    void operator=(Circle B){
        x = B.x;
        y = B.y;
        r = B.r;
        return;
    }
};

Circle* getFace(Mat& image){
    cvtColor(image,image,COLOR_BGR2GRAY);
    vector<Rect> faces;
    CascadeClassifier cl("../haarcascade_frontalface_default.xml");
    cl.detectMultiScale(image,faces, 1.1,3, 0,Size(200,200),Size(1800,1800));
    for(auto u : faces){
        int x,y,w,h;
        x=u.x;y=u.y;w=u.width;h=u.height;
        // circle(image, Point((2*x+h)/2,(2*y+w)/2), max(w,h)/2, COLOR_BayerGB2RGB_VNG, 5, LINE_8, 0);
        Circle * ret = new Circle(x+h/2,y+w/2,max(h,w)/2.2);
        return ret;
    }
    /*imshow("i",image);
    waitKey(0);*/
    Circle* ret = new Circle(256,256,125);
    return ret;
}
struct pack{
    int x,y,depth;
    Mat* a;
    Mat* b;
    pack(){}
    pack(int p1,int p2,int p3,Mat& mat1,Mat& mat2){
        x = p1;
        y = p2;
        depth = p3;
        a = &mat1;
        b = &mat2;
    }
};

void dfs(int x,int y, int depth, Mat& result, Mat& currentMatrix){

    Vec3b color = result.at<Vec3b>(Point(x,y));
    if(color[0] == color[1] && color[2] == color[1] && color[1] == 0){
        /// we're ok
    }else return;
    if(depth >4)
        return;
    Mat shrunk;
    cv::resize(currentMatrix, shrunk, cv::Size(),1.0/GOLDEN_RATIO, 1.0/GOLDEN_RATIO);
    /*imshow("shrunk", shrunk);
    //cout<<shrunk.rows<<' '<<shrunk.cols<<endl<<currentMatrix.rows<<' '<<currentMatrix.cols<<endl;

    waitKey(0);*/
    int dx[] = {0,1,-1,0};
    int dy[] = {-1,0,0,1};

    int upX = x - currentMatrix.rows/2;
    int upY = y - currentMatrix.cols/2;
    int diameter = currentMatrix.cols;
    for(int i=upX;i-upX<diameter;i++){
        for(int j=upY;j-upY<diameter;j++){
            Vec3b naskh = currentMatrix.at<Vec3b>(Point(i-upX,j-upY));
            if(naskh[0] == 0 && naskh[1] == 0 && naskh[2]==0)continue;

            result.at<Vec3b>(Point(i,j)) = naskh;
        }
    }
    namedWindow("result", WINDOW_GUI_EXPANDED);
    imshow("result",result);
    waitKey(0);
    for(int t=0;t<4;t++){
        int nx = x + dx[t] * (currentMatrix.rows + shrunk.rows)/2.0;
        int ny = y + dy[t] * (currentMatrix.cols + shrunk.cols)/2.0;
        dfs(nx,ny, depth + 1, result, shrunk);
    }
}


Mat* crossOver(Mat& p1, Mat& p2) {
    Mat* child = new Mat(512, 512, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            for (int k = 0; k < 3; k++) {
                child->at<Vec3b>(i, j)[k] = (p1.at<Vec3b>(i, j)[k] + p2.at<Vec3b>(i, j)[k]) / 2;

            }
        }
    }
    return child;
}
void mutate(Mat& child){

}

bool cmp(Mat& a,Mat& b){
    return 1;
}

void breed(Mat& result, vector<Mat>& population){
    vector<Mat> newPopulation;

    for(int i=0;i<55;i++){
        for(int j=i+1;j<55;j++){
            Mat child = *crossOver(population[i], population[j]);
            if(rand()%4==0)
                mutate(child);
            newPopulation.push_back(child);
        }
    }
    sort(newPopulation.begin(),newPopulation.end(), cmp);
    /// Certain parts of the new population will mutate 10% to make the algorithm work faster however it could be set to any value


    for(int mutateCounter = 0;mutateCounter<20;mutateCounter++){
        int i = rand() % 200;

    }
}

void geneticStart(Mat& result){
    vector<Mat> population(55 ,Mat(512,512, CV_8UC3, Scalar(0,0,0)));

}

int main( int argc, const char** argv ) {


    Mat image = imread("../abdul.png");

    Mat original = image.clone();
    Circle fractalFace;
    fractalFace = *getFace(image);

    int HugeScaller = 1000;
    circle(original, Point(fractalFace.x,fractalFace.y),fractalFace.r+HugeScaller/2, cv::Scalar(0,0,0),HugeScaller);
    // circle(original, Point(fractalFace.x,fractalFace.y),fractalFace.r-5, cv::Scalar(0,0,0),10);
    Mat root = original(Rect(fractalFace.x-fractalFace.r,fractalFace.y-fractalFace.r,2*fractalFace.r,2*fractalFace.r));

    namedWindow("Face",WINDOW_NORMAL);
    cv::resize(root,root,cv::Size(),150.0/root.cols, 150.0/root.cols);
    Mat img2;
    Mat result(512,512, CV_8UC3, Scalar(0,0,0));
    dfs(512/2,512/2, -1, result, root);
    geneticStart(result);
    imshow("Face",result);
    imwrite("../Output.jpg", result);
    waitKey(0);
}










