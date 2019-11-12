package main
import(
	"os"
	"fmt"
    "math"
    "reflect"
    "image"
    _ "image/gif"
    "image/jpeg"
    "image/color"
    _ "image/png"
    "github.com/nfnt/resize"
)
func u32_u8(colorRgb color.Color) (uint8,uint8,uint8,uint8){
	r1,g1,b1,a1 := colorRgb.RGBA()
	r_uint8 := uint8(r1>>8)  //转换为 255 值
    g_uint8 := uint8(g1>>8)
    b_uint8 := uint8(b1>>8)
    a_uint8 := uint8(a1>>8)
	return r_uint8,g_uint8,b_uint8,a_uint8
}
func abscha(im image.Image,x1 int,y1 int,x2 int,y2 int) float64{
	colorRgb1 := im.At(int(x1), int(y1))  
	r1,g1,b1,_ := u32_u8(colorRgb1)
	colorRgb2 := im.At(int(x2), int(y2))  
	r2,g2,b2,_ := u32_u8(colorRgb2)	
	y:=math.Abs(float64(r1)-float64(r2))+math.Abs(float64(g1)-float64(g2))+math.Abs(float64(b1)-float64(b2))
	return y
}
// func expanw(im image.Image,m int,n int,num int) image.Image{
// 	if(num==0){
// 		return im
// 	}
// 	energy:=make([][]float64,m)
//     for i:=0;i<m;i++{
//     	for j:=0;j<n;j++{
// 			energy[i]=append(energy[i],10000)
// 		}
// 	}
// 	indexs:=make([]int,m)

// 	//first line
// 	for int i:=0;i<1;i++ {
// 		for int j:=1;j<n-1;j++ {
// 			energy[i][j]=abscha(im,)
// 			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i+1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
// 			// +abs(img.ptr<cv::Vec3b>(i+1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
// 			// +abs(img.ptr<cv::Vec3b>(i+1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2]);
// 		}
// 	}
// 	for(int i=1;i<m-1;i++){
// 		for(int j=1;j<n-1;j++){
// 			energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j-1][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
// 			+abs(img.ptr<cv::Vec3b>(i)[j-1][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
// 			+abs(img.ptr<cv::Vec3b>(i)[j-1][2]-img.ptr<cv::Vec3b>(i)[j+1][2])
// 			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i+1)[j][2])
// 			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i+1)[j][1])
// 			+abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i+1)[j][0])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
// 		}
// 	}

// 	//last line
// 	for(int i=m-1;i<m;i++){
// 		for(int j=1;j<n-1;j++){
// 			energy[i][j]=abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
// 			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
// 			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
// 		}
// 	}

// 	//first cols
// 	for(int i=1;i<m;i++){
// 		for(int j=0;j<1;j++){
// 			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
// 			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
// 			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
// 			energy[i][j]=energy[i][j+1];
// 		}
// 	}

// 	//last cols
// 	for(int i=1;i<m;i++){
// 		for(int j=n-1;j<n;j++){
// 			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
// 			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
// 			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
// 			energy[i][j]=energy[i][j-1];
// 		}
// 	}
	
// 	for(int k=0;k<num;k++){
// 		int minv=9999;
// 		for(int j=0;j<n;j++){
// 			if(minv>energy[m-1][j]){
// 				minv=energy[m-1][j];
// 				indexs[m-1][k]=j;
// 				// cout<<j<<endl;
// 			}
// 		energy[m-1][indexs[m-1][k]]=60000;
// 		}
// 	}


// 	for(int k=0;k<num;k++){

// 		for(int i=m-2;i>=0;i--){
// 			int j=indexs[i+1][k];
// 			if(indexs[i+1][k]!=0 && indexs[i+1][k]!=n-1){
// 				int a=min(min(energy[i][j-1],energy[i][j]),energy[i][j+1]);
// 				if(energy[i][j]==a){
// 					indexs[i][k]=j;
// 				}else if(energy[i][j-1]==a){
// 					indexs[i][k]=j-1;
// 				}else{
// 					indexs[i][k]=j+1;
// 				}
// 			}else if(indexs[i+1][k]==0){
// 				int a=min(energy[i][j],energy[i][j+1]);
// 				if(energy[i][j]==a){
// 					indexs[i][k]=j;
// 				}else{
// 					indexs[i][k]=j+1;
// 				}
// 			}else{
// 				int a=min(energy[i][j],energy[i][j-1]);
// 				if(energy[i][j]==a){
// 					indexs[i][k]=j;
// 				}else{
// 					indexs[i][k]=j-1;
// 				}
// 			}
// 		}
// 	}

// 	for(int i=0;i<m;i++){
// 		for(int l1=0;l1<num;l1++){
// 			int kz=1;
// 			int tmp;
// 			for(int l2=0;l2<num;l2++){
// 				if(indexs[i][l2]>indexs[i][l2+1]){
// 					kz=0;
// 					tmp=indexs[i][l2+1];
// 					indexs[i][l2+1]=indexs[i][l2];
// 					indexs[i][l2]=tmp;
// 				}
// 			}
// 			if (kz){
// 				break;
// 			}
// 		}
// 		// cout<<"good"<<endl;
// 		// for(int l1=0;l1<num;l1++){
// 		// 	indexs[i][l1]=0;
// 		// 	cout<<indexs[i][l1]<<endl;
// 		// }
// 		// cout<<"good0"<<endl;
// 		int newind=num+n-1;
// 		int inind=n-1;
// 		int index=num-1;
// 		while (newind>=0){
// 				// cout<<inind<<endl;
// 				newimg.ptr<cv::Vec3b>(i)[newind][0]=img.ptr<cv::Vec3b>(i)[inind][0];
// 				newimg.ptr<cv::Vec3b>(i)[newind][1]=img.ptr<cv::Vec3b>(i)[inind][1];
// 				newimg.ptr<cv::Vec3b>(i)[newind][2]=img.ptr<cv::Vec3b>(i)[inind][2];
// 				newind-=1;
// 				while(inind==indexs[i][index] && index>=0){
// 					newimg.ptr<cv::Vec3b>(i)[newind][0]=img.ptr<cv::Vec3b>(i)[inind][0];
// 					newimg.ptr<cv::Vec3b>(i)[newind][1]=img.ptr<cv::Vec3b>(i)[inind][1];
// 					newimg.ptr<cv::Vec3b>(i)[newind][2]=img.ptr<cv::Vec3b>(i)[inind][2];
// 					newind=newind-1;
// 					index=index-1;
// 				}
// 				inind-=1;


// 		}

// 	}

// }
// func typeof(v interface{}) string {
//     return fmt.Sprintf("%T", v)
// }
func typeof(v interface{}) string {
    return reflect.TypeOf(v).String()
}
func semw(im image.Image,m int,n int) image.Image{
	energy:=make([][]float64,m)
	// fmt.Println(typeof(energy))
	// fmt.Println(len(energy))
	// fmt.Println((energy[0]))
    // var energy [m][n]float64
    for i:=0;i<m;i++{
    	for j:=0;j<n;j++{
			energy[i]=append(energy[i],10000)
		}
	}
	// fmt.Println(energy)
	// fmt.Println("hhhhhhhhhhhhhhhhhhhh")
	indexs:=make([]int,m)
	for i:=0;i<1;i++{
		for j:=1;j<n-1;j++{
			energy[i][j]=abscha(im,j,i+1,j,i)
			// abs(img.ptr<cv::Vec3b>(i+1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
			// +abs(img.ptr<cv::Vec3b>(i+1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
			// +abs(img.ptr<cv::Vec3b>(i+1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2]);
		}
	}
	for i:=1;i<m-1;i++{
		for j:=1;j<n-1;j++{
			energy[i][j]=abscha(im,j-1,i,j+1,i)+abscha(im,j,i-1,j,i+1)+math.Min(math.Min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j])
		
		}
	}
	for i:=m-1;i<m;i++{
		for j:=1;j<n-1;j++{
			energy[i][j]=abscha(im,j,i-1,j,i)+math.Min(math.Min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j])
		}
	}

	//first cols
	for i:=1;i<m;i++{
		for j:=0;j<1;j++{
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
			energy[i][j]=energy[i][j+1]
		}
	}
	// fmt.Println("12")
	//last cols
	for i:=1;i<m;i++{
		for j:=n-1;j<n;j++{
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
			energy[i][j]=energy[i][j-1]
		}
	}
	// for i:=m-1;i<m;i++{
	// 	for j:=0;j<n;j++{
	// 		fmt.Println(energy[i][j])
	// 	}
	// }
	var minv float64=9999
	for j:=0;j<n;j++{
		// fmt.Println(energy[m-1][j])
		if(minv>energy[m-1][j]){
			minv=energy[m-1][j]
			indexs[m-1]=j

		}

	}
	// fmt.Println(indexs[m-1])
	for i:=m-2;i>=0;i--{
		j:=indexs[i+1]
		if(indexs[i+1]!=0 && indexs[i+1]!=n-1){
			a :=math.Min(math.Min(energy[i][j-1],energy[i][j]),energy[i][j+1])
			if(energy[i][j]==a){
				indexs[i]=j
			}else if(energy[i][j-1]==a){
				indexs[i]=j-1
			}else{
				indexs[i]=j+1
			}
		}else if(indexs[i+1]==0){
			a:=math.Min(energy[i][j],energy[i][j+1])
			if(energy[i][j]==a){
				indexs[i]=j
			}else{
				indexs[i]=j+1
			}
		}else{
			a:=math.Min(energy[i][j],energy[i][j-1])
			if(energy[i][j]==a){
				indexs[i]=j
			}else{
				indexs[i]=j-1
			}
		}
	}

	matimg := image.NewRGBA(image.Rect(0,0,n-1,m)) //new 一个新的图片
	
	// cout<<"good"<<endl;
	for i:=0;i<m;i++{
		qs:=indexs[i]
		// fmt.Println(qs)
		for j:=0;j<qs;j++{
			colorRgb := im.At(j,i)
			r1,g1,b1,a1 := u32_u8(colorRgb)
			
			matimg.SetRGBA(j,i,color.RGBA{r1, g1, b1,a1})
		}
		for j:=qs;j<n-1;j++{
			colorRgb := im.At(j+1,i)
			r1,g1,b1,a1 := u32_u8(colorRgb)

			matimg.SetRGBA(j,i,color.RGBA{r1, g1, b1,a1})
		}
	}
	return matimg
	// fmt.Println(energy[m-1][n-1])
	// fmt.Println(g_uint8)
	// fmt.Println(b_uint8)
	// fmt.Println(a_uint8)
}

func main(){
	imagePath := "/home/qin/data/cat.jpeg"
    file, _ := os.Open(imagePath)
    fmt.Println(file)
    img, _, _ := image.Decode(file)

    m := img.Bounds().Max.Y
    n := img.Bounds().Max.X

    expanh := 200
    expanw := 10
    neww := 0
    newh := 0
    sew := 0
    seh := 0
    if expanw>expanh{
    	neww = n+expanw
    	newh = m+expanw
    	sew =0
    	seh =expanw-expanh
    }else{
    	neww = n+expanh
    	newh = m+expanh
    	sew = expanh-expanw
    	seh = 0
    }

    im := resize.Resize(uint(neww), uint(newh), img, resize.Lanczos3)

    m = im.Bounds().Max.Y
    n = im.Bounds().Max.X

    for i:=0;i<sew;i++{
		im =semw(im,m,n)
		n-=1
    }


    //Rotate 90
	rotate9 := image.NewRGBA(image.Rect(0, 0, im.Bounds().Dy(), im.Bounds().Dx()))
	for x := im.Bounds().Min.Y; x < im.Bounds().Max.Y; x++ {
	    for y := im.Bounds().Max.X - 1; y >= im.Bounds().Min.X; y-- {
	        rotate9.Set(im.Bounds().Max.Y-x, y, im.At(y, x))
	    }
	}    
	rotate90 := image.Image(rotate9)
	m = rotate90.Bounds().Max.Y
    n = rotate90.Bounds().Max.X
    for i:=0;i<seh;i++{
		rotate90 =semw(rotate90,m,n)
		n-=1
    }
    //Rotate 270
    imgb:=image.Image(rotate90)
	rotate270 := image.NewRGBA(image.Rect(0, 0, m, n))
	for x := imgb.Bounds().Min.Y; x < imgb.Bounds().Max.Y; x++ {
	    for y := imgb.Bounds().Max.X - 1; y >= imgb.Bounds().Min.X; y-- {
	        rotate270.Set(x, imgb.Bounds().Max.X-y, imgb.At(y, x))
	    }
	}
	// fmt.Println(im)
    f, _ := os.Create("/home/qin/go.jpg")
    defer f.Close()
    jpeg.Encode(f,rotate270,nil)
}