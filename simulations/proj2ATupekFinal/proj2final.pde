// Ann Tupek
// CS681
// Project 2 Final
// Due 4/29/15
//
// Traffic simulation


/* @pjs preload = "Background.png"; */

PImage bg;

//seg1X
int[] i55Exa = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
				64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 116, 120,
				124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168,
				172, 176};
//seg2X
int[] i55Exb = {180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 224,
				228, 232, 236, 240, 244, 248, 252, 256, 260, 264, 268, 272,
				276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316, 320,
				324, 328, 332, 336, 340, 344, 348, 352, 356, 360, 364, 368,
				372, 376, 380, 384, 388, 392, 396, 400, 404, 408, 412, 416,
				420, 424, 428, 432, 436, 440, 444, 448, 452, 456, 460, 464,
				468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508, 512,
				516, 520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560,
				564, 568, 572, 576, 580, 584, 588, 592, 596, 600, 604, 608,
				612, 616, 620, 624};
//seg3X
int[] i55Exc = {628, 632, 636, 640, 644, 648, 652, 656, 660, 664, 668, 672,
				676, 680, 684, 688, 692, 696, 700, 704, 708, 712, 716, 720,
				724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764, 768,
				772, 776, 780, 784, 788, 792};
//seg1Y
int[] i55Eya = {74, 76, 78, 80, 81, 83, 85, 87, 89, 91, 92, 93, 95, 97, 99,
				101, 103, 105, 107, 109, 111, 113, 116, 118, 119, 121, 123,
				125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 144, 146,
				148, 150, 152, 154, 156};
//seg2Y
int[] i55Eyb = {158, 160, 162, 164, 168, 170, 172, 173, 175, 177, 178, 181,
				183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205,
				207, 209, 211, 215, 217, 220, 223, 225, 227, 229, 231, 233,
				235, 237, 239, 241, 244, 246, 248, 250, 253, 255, 256, 257,
				259, 260, 262, 264, 266, 268, 274, 277, 279, 281, 283, 285,
				287, 289, 292, 295, 297, 299, 301, 303, 305, 307, 309, 311,
				313, 316, 318, 320, 322, 324, 328, 330, 332, 334, 336, 338,
				340, 343, 345, 347, 349, 352, 355, 358, 361, 363, 366, 369,
				370, 372, 374, 376, 380, 384, 386, 390, 393, 395, 398, 401,
				404, 407, 410, 412};
//seg3Y
int[] i55Eyc = {415, 419, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450,
				453, 456, 460, 464, 468, 473, 477, 480, 483, 487, 490, 493,
				497, 501, 505, 509, 513, 517, 521, 525, 529, 532, 536, 540,
				544, 548, 552, 556, 560, 564};
//seg4X
int[] i55Wxa = {772, 768, 764, 760, 756, 752, 748, 744, 740, 736, 732, 728,
				724};
//seg5X
int[] i55Wxb = {720, 716, 712, 708, 704, 700, 696, 692, 688, 684, 680, 676,
				672, 668, 664, 660, 656, 652, 648, 644, 640, 636, 632, 628,
				624, 620, 616, 612, 608, 604, 600, 596, 592, 588, 584, 580,
				576, 572, 568, 564, 560, 556, 552, 548, 544, 540, 536, 532,
				528, 524, 520, 516, 512, 508, 504, 500, 496, 492, 488, 484,
				480, 476, 472, 467, 464, 460, 456, 452, 448, 444, 440, 436,
				432, 428, 424, 420, 416, 412, 408, 404, 400, 396, 392, 388,
				384, 380, 376, 372, 368, 364, 360, 356, 352, 348, 344, 340,
				336, 332, 328, 324, 320, 316, 312, 308, 304, 300, 296, 292,
				288, 284, 280, 276, 272, 268};
//seg6X
int[] i55Wxc = {264, 260, 256, 252, 248, 244, 240, 236, 232, 228, 224, 220,
				216, 212, 208, 204, 200, 196, 192, 188, 184, 180, 176, 172,
				168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124,
				120, 116, 112, 108, 104, 100, 96, 92, 88, 84, 80, 76, 72,
				68, 64, 60, 56, 52, 48, 44, 40, 36,	32, 28, 24, 20, 16,
				12, 8, 4, 0};
//seg4Y
int[] i55Wya = {563, 559, 555, 551, 547, 543, 539, 535, 531, 527, 524, 520, 
				517};
//seg5Y
int[] i55Wyb = {513, 509, 505, 501, 497, 494, 490, 486, 483, 480, 477, 474,
				471, 468, 465, 461, 456, 452, 449, 446, 443, 440, 437, 434,
				431, 428, 425, 422, 419, 416, 413, 410, 407, 404, 401, 399,
				395, 392, 389, 387, 385, 381, 377, 375, 373, 371, 369, 367,
				365, 363, 360, 358, 356, 354, 352, 349, 346, 343, 341, 338,
				335, 332, 330, 328, 326, 324, 322, 321, 320, 318, 316, 312,
				310, 308, 306, 304, 301, 299, 297, 295, 293, 291, 288, 286,
				283, 281, 279, 277, 275, 273, 270, 268, 266, 264, 261, 259,
				257, 255, 253, 251, 248, 246, 244, 242, 240, 237, 235, 233,
				231, 229, 227, 225, 223, 221};
//seg6Y
int[] i55Wyc = {218, 215, 213, 211, 209, 207, 205, 203, 200, 198, 196, 194,
				192, 189, 187, 185, 183, 181, 179, 177, 175, 173, 171, 170,
				168, 166, 164, 162, 160, 158, 156, 154, 152, 150, 149, 147,
				145, 143, 141, 139, 138, 136, 134, 132, 131, 129, 128, 126,
				124, 122, 120, 118, 116, 114, 113, 111, 109, 107, 105, 103,
				101, 99, 97, 95, 93, 91, 89};
//seg7X
int[] i83Nxa = {462, 462, 462, 462, 462, 462, 462, 462, 462, 462, 462, 462, 
				462, 462, 462, 462, 462, 462, 462, 462, 461, 461, 461, 461, 
				461};
//seg8X
int[] i83Nxb = {460, 460, 460, 460, 460, 460, 460, 460, 460, 460, 460, 460,
				460, 460, 460, 459, 459, 459, 459, 459, 459, 459, 459, 459,
				459, 458, 458, 458, 458, 458, 458, 458, 458, 458, 458, 457,
				457, 457, 457, 457, 457, 457};
//seg9X
int[] i83Nxc = {457, 457, 457, 456, 456, 456, 456, 456, 456, 456, 456, 456,
				456, 456, 456, 456, 456, 456, 456, 456, 456, 456, 456, 455,
				455, 455, 455, 455, 455, 455, 455, 455, 455};
//seg10X
int[] i83Nxd = {454, 454, 454, 454, 454, 454, 454, 454, 454, 454, 453, 453,
				453, 453, 453, 453, 453, 453, 453, 453, 452, 452, 452, 452,
				452, 452, 452, 452, 452, 452};
//seg11X
int[] i83Nxe = {451, 451, 451, 451, 451, 451, 451, 451, 451, 451, 450, 450,
				450, 450};
//seg7Y
int[] i83Nya = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
				64, 68, 72, 76, 80, 84, 88, 92, 96};
//seg8Y
int[] i83Nyb = {100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 
				148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 
				196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 
				244, 248, 252, 256, 260, 264};
//seg9Y
int[] i83Nyc = {268, 272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312,
				316, 320, 324, 328, 332, 336, 340, 344, 348, 352, 356, 360,
				364, 368, 372, 376, 380, 384, 388, 392, 396};
//seg10Y
int[] i83Nyd = {400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444,
				448, 452, 456, 460, 464, 468, 472, 476, 480, 484, 488, 492,
				496, 500, 504, 508, 512, 516};
//seg11Y
int[] i83Nye = {520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560, 564,
				568, 572};
//seg12X
int[] i83Sxa = {435, 435, 435, 435, 435, 435, 435, 435, 435, 435};
//seg13X
int[] i83Sxb = {436, 436, 436, 436, 436, 436, 436, 436, 436, 436, 437, 437,
				437, 437, 437, 437, 437, 437, 437, 437, 438, 438, 438, 438,
				438, 438, 438, 438, 438, 438, 439, 439, 439, 439, 439, 439,
				439, 439, 439, 439, 439};
//seg14X
int[] i83Sxc = {439, 439, 439, 439, 439, 439, 439, 439, 439, 440, 440, 440,
				440, 440, 440, 440, 440, 440, 440, 441, 441, 441, 441, 441,
				441, 441, 441, 441, 441};
//seg15X
int[] i83Sxd = {443, 443, 443, 443, 443, 443, 443, 443, 443, 443, 444, 444,
				444, 444, 444, 444, 444, 444, 444, 444, 445, 445, 445, 445,
				445, 445, 445, 445, 445, 445, 446, 446, 446, 446, 446, 446,
				446, 446, 446, 446};
//seg16X
int[] i83Sxe = {447, 447, 447, 447, 447, 447, 447, 447, 447, 447, 448, 448, 
				448, 448, 448, 448, 448, 448, 448, 448, 448, 448, 448, 448};
//seg12Y
int[] i83Sya = {572, 568, 564, 560, 556, 552, 548, 544, 540, 536};
//seg13Y
int[] i83Syb = {532, 528, 524, 520, 516, 512, 508, 504, 500, 496, 492, 488, 484,
				480, 476, 472, 468, 464, 460, 456, 452, 448, 444, 440, 436,
				432, 428, 424, 420, 416, 412, 408, 404, 400, 396, 392, 388,
				384, 380, 376, 372};
//seg14Y
int[] i83Syc = {368, 364, 360, 356, 352, 348, 344, 340, 336, 332, 328, 324,
				320, 316, 312, 308, 304, 300, 296, 292, 288, 284, 280, 276,
				272, 268, 264, 260, 256};
//seg15Y
int[] i83Syd = {252, 248, 244, 240, 236, 232, 228, 224, 220, 216, 212, 208,
				204, 200, 196, 192, 188, 184, 180, 176, 172, 168, 164, 160,
				156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112,
				108, 104, 100, 96};
//seg16Y
int[] i83Sye = {92, 88, 84, 80, 76, 72, 68, 64, 60, 56, 52, 48, 44, 40, 36,
				32, 28, 24, 20, 16, 12, 8, 4, 0};
//seg17X
int[] i55e83sXa = {176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 256};
//seg18X
int[] i55e83sXb = {296, 300, 304, 332, 344, 352, 360, 368, 380, 392, 400, 412,
				420, 428, 432, 440, 444, 447};
//seg17Y
int[] i55e83sYa = {156, 157, 158, 159, 161, 163, 164, 166, 168, 169, 171, 187};
//seg18Y
int[] i55e83sYb = {205, 205, 205, 205, 203, 200, 197, 194, 188, 180, 173, 161,
				151, 140, 130, 112, 98, 92};
//seg19X
int[] i55e83nXa = {296, 300, 304, 332, 352, 372, 376, 380};
//seg20X
int[] i55e83nXb = {384, 400, 420, 436, 468};
//seg21X
int[] i55e83nXc = {484, 500, 520, 524, 536, 544, 552, 554, 556, 556, 556, 554,
				550, 540, 532, 524, 516, 504, 496, 488, 480, 472, 468, 464};
//seg19Y
int[] i55e83nYa = {205, 209, 212, 231, 244, 256, 258, 259};
//seg20Y
int[] i55e83nYb = {260, 270, 281, 290, 308};
//seg21Y
int[] i55e83nYc = {316, 318, 318, 317, 312, 306, 293, 286, 280, 273, 266, 258,
				250, 239, 234, 230, 228, 228, 230, 234, 240, 250, 260, 453};
//seg22X
int[] i55w83nXa = {724, 720, 716, 708, 696, 684, 668, 652, 640, 628, 612};
//seg23X
int[] i55w83nXb = {608, 604, 596, 588, 564, 556, 544, 528, 516, 500, 488, 484,
				476, 472, 468, 464, 460, 459};
//seg22Y
int[] i55w83nYa = {525, 523, 520, 514, 504, 494, 482, 470, 460, 451, 439};
//seg23Y
int[] i55w83nYb = {437, 436, 433, 432, 432, 434, 437, 444, 450, 462, 472, 476,
				485, 491, 497, 506, 515, 520};
//seg24X
int[] i55w83sXa = {608, 604, 596, 588, 564, 532, 528};
//seg25X
int[] i55w83sXb = {524, 512, 500, 492, 467, 436, 424};
//seg26X
int[] i55w83sXc = {420, 412, 404, 400, 392, 384, 372, 364, 356, 352, 348, 348,
				352, 356, 360, 364, 372, 376, 384, 400, 404, 412, 420, 428,
				432, 436, 439};
//seg24Y
int[] i55w83sYa = {437, 433, 426, 420, 402, 381, 379};
//seg25Y
int[] i55w83sYb = {377, 370, 363, 358, 344, 326, 320};
//seg26Y
int[] i55w83sYc = {319, 317, 316, 315, 315, 316, 321, 326, 334, 342, 352, 370,
				380, 388, 393, 396, 401, 403, 406, 406, 405, 402, 397, 389,
				383, 376, 368};
//seg27X
int[] i83n55wXa = {462, 463, 464, 465, 467, 470, 475, 481, 488, 492, 504, 512,
				520, 528, 532, 536, 536, 534, 532, 530, 528, 524};
//seg28X
int[] i83n55wXb = {420, 412, 372, 332, 313, 306, 302};
//seg27Y
int[] i83n55wYa = {400, 404, 408, 412, 416, 424, 432, 436, 440, 442, 442, 440,
				436, 428, 420, 410, 398, 394, 390, 385, 382, 377};
//seg28Y
int[] i83n55wYb = {319, 313, 291, 269, 259, 256, 254};
//seg29X
int[] i83n55eXa = {468, 469, 470, 471, 472, 473, 474, 476, 481, 484, 488, 493,
				498, 505, 513, 522, 530, 539, 548, 555, 560, 564, 566, 566,
				566, 566, 566, 567, 568, 570, 575, 580, 584, 588, 592};
//seg30X
int[] i83n55eXb = {596, 600, 604, 608, 612, 616, 620, 624};
//seg29Y
int[] i83n55eYa = {100, 104, 108, 112, 116, 120, 132, 140, 152, 160, 168, 176,
				184, 192, 200, 208, 216, 224, 232, 240, 248, 256, 264, 280,
				293, 306, 324, 332, 336, 345, 355, 363, 370, 376, 380};
//seg30Y
int[] i83n55eYb = {384, 388, 392, 396, 400, 404, 408, 412};
//seg31X
int[] i83s55eXa = {443, 442, 441, 440, 440, 439, 437, 433, 425, 418, 410, 396,
				388, 382, 377, 374, 370, 369, 368, 368, 370, 375, 376, 380,
				384};
//seg32X
int[] i83s55eXb = {484, 488, 492, 500, 512, 524, 548, 570, 584, 588, 592, 596};
//seg31Y
int[] i83s55eYa = {252, 248, 244, 240, 228, 224, 216, 208, 200, 196, 193, 193,
				196, 200, 204, 208, 216, 220, 224, 236, 240, 248, 252, 255,
				260};
//seg32Y
int[] i83s55eYb = {316, 320, 322, 327, 334, 340, 355, 369, 378, 380, 382, 384};
//seg33X
int[] i83s55wXa = {436, 434, 433, 432, 432, 430, 429, 428, 427, 424, 420, 417,
				412, 406, 400, 392, 383, 374, 366, 357, 350, 344, 340, 338,
				337, 337, 337, 336, 335, 334, 333, 330, 327, 323, 318, 313,
				306, 302};
//seg34X
int[] i83s55wXb = {292, 288, 284, 280, 276, 272, 268, 264};
//seg33Y
int[] i83s55wYa = {532, 528, 524, 520, 516, 508, 500, 496, 492, 484, 476, 468,
				460, 452, 444, 436, 428, 420, 412, 404, 396, 388, 380, 372,
				368, 356, 344, 340, 324, 312, 304, 296, 288, 280, 272, 266,
				258, 25};
//seg34Y
int[] i83s55wYb = {247, 244, 241, 238, 235, 232, 229, 226};

class Segment {
  string name;
  int[] x_array;
  int[] y_array;
  float total_length;
  int start_index;
  int end_index;
  int numFollows;
  Segment[] follows = new Segment[numFollows];

}

Segment[] segmentArray = new Segment[34];

class Car {
  string id;
  string currSegment;
  float distance;
  float speed;
  float desiredSpeed;
  float car_x;
  float car_y;
  int carColorR;
  int carColorG;
  int carColorB;
}

int numCars = 15;

Car[] carArray = new Car[numCars];

int lastUpdateTime = 0;

class Path{
	string name;
	Segment[] pathSegments;
}

  
//For debugging paths-they're still a little crooked...
/*void mouseClicked()
{
    alert(mouseX, mouseY);
}*/

float segDistance(int[] segmentX, int[] segmentY)
{
	float segDistance = 0.0;
	for(int i =0; i<segmentX.length()-1; i++)
	{
		segDistance+=sqrt((segmentX[i+1]-segmentX[i])*(segmentX[i+1]-segmentX[i]) +
							(segmentY[i+1]-segmentY[i])*(segmentY[i+1]-segmentY[i]));
	}
	return segDistance;

}

void setupSegments()
{
	segmentArray[0] = new Segment;
	segmentArray[0].name = "i55E_1";
	segmentArray[0].x_array = i55Exa;
	segmentArray[0].y_array = i55Eya;
	segmentArray[0].start_index = 0;
	segmentArray[0].end_index = 43;
	segmentArray[0].total_length=segDistance(i55Exa, i55Eya);
	segmentArray[0].numFollows = 2;
	//println(segmentArray[0].total_length);

	segmentArray[1] = new Segment;
	segmentArray[1].name = "i55E_2";
	segmentArray[1].x_array = i55Exb;
	segmentArray[1].y_array = i55Eyb;
	segmentArray[1].start_index = 0;
	segmentArray[1].end_index = 111;
	segmentArray[1].total_length=segDistance(i55Exb, i55Eyb);
	segmentArray[1].numFollows = 1;
	//println(segmentArray[1].total_length);

	segmentArray[2] = new Segment;
	segmentArray[2].name = "i55E_3";
	segmentArray[2].x_array = i55Exc;
	segmentArray[2].y_array = i55Eyc;
	segmentArray[2].start_index = 0;
	segmentArray[2].end_index = 43;
	segmentArray[2].total_length=segDistance(i55Exc, i55Eyc);
	segmentArray[2].numFollows = 1;
	//println(segmentArray[2].total_length);

	segmentArray[3] = new Segment;
	segmentArray[3].name = "i55W_1";
	segmentArray[3].x_array = i55Wxa;
	segmentArray[3].y_array = i55Wya;
	segmentArray[3].start_index = 0;
	segmentArray[3].end_index = 12;
	segmentArray[3].total_length=segDistance(i55Wxa, i55Wya);
	segmentArray[3].numFollows=2;
	//println(segmentArray[3].total_length);

	segmentArray[4] = new Segment;
	segmentArray[4].name = "i55W_2";
	segmentArray[4].x_array = i55Wxb;
	segmentArray[4].y_array = i55Wyb;
	segmentArray[4].start_index = 0;
	segmentArray[4].end_index = 113;
	segmentArray[4].total_length=segDistance(i55Wxb, i55Wyb);
	segmentArray[4].numFollows = 1;
	//println(segmentArray[4].total_length);

	segmentArray[5] = new Segment;
	segmentArray[5].name = "i55W_3";
	segmentArray[5].x_array = i55Wxc;
	segmentArray[5].y_array = i55Wyc;
	segmentArray[5].start_index = 0;
	segmentArray[5].end_index = 66;
	segmentArray[5].total_length=segDistance(i55Wxc, i55Wyc);
	segmentArray[5].numFollows=1;
	//println(segmentArray[5].total_length);

	segmentArray[6] = new Segment;
	segmentArray[6].name = "i83N_1";
	segmentArray[6].x_array = i83Nxa;
	segmentArray[6].y_array = i83Nya;
	segmentArray[6].start_index = 0;
	segmentArray[6].end_index = 24;
	segmentArray[6].total_length=segDistance(i83Nxa, i83Nya);
	segmentArray[6].numFollows = 2;
	//println(segmentArray[6].total_length);

	segmentArray[7] = new Segment;
	segmentArray[7].name = "i83N_2";
	segmentArray[7].x_array = i83Nxb;
	segmentArray[7].y_array = i83Nyb;
	segmentArray[7].start_index = 0;
	segmentArray[7].end_index = 41;
	segmentArray[7].total_length=segDistance(i83Nxb, i83Nyb);
	segmentArray[7].numFollows=1;
	//println(segmentArray[7].total_length);

	segmentArray[8] = new Segment;
	segmentArray[8].name = "i83N_3";
	segmentArray[8].x_array = i83Nxc;
	segmentArray[8].y_array = i83Nyc;
	segmentArray[8].start_index = 0;
	segmentArray[8].end_index = 32;
	segmentArray[8].total_length=segDistance(i83Nxc, i83Nyc);
	segmentArray[8].numFollows = 2;
	//println(segmentArray[8].total_length);

	segmentArray[9] = new Segment;
	segmentArray[9].name = "i83N_4";
	segmentArray[9].x_array = i83Nxd;
	segmentArray[9].y_array = i83Nyd;
	segmentArray[9].start_index = 0;
	segmentArray[9].end_index = 29;
	segmentArray[9].total_length=segDistance(i83Nxd, i83Nyd);
	segmentArray[9].numFollows=1;
	//println(segmentArray[9].total_length);

	segmentArray[10] = new Segment;
	segmentArray[10].name = "i83N_5";
	segmentArray[10].x_array = i83Nxe;
	segmentArray[10].y_array = i83Nye;
	segmentArray[10].start_index = 0;
	segmentArray[10].end_index = 13;
	segmentArray[10].total_length=segDistance(i83Nxe, i83Nye);
	segmentArray[10].numFollows=1;
	//println(segmentArray[10].total_length);

	segmentArray[11] = new Segment;
	segmentArray[11].name = "i83S_1";
	segmentArray[11].x_array = i83Sxa;
	segmentArray[11].y_array = i83Sya;
	segmentArray[11].start_index = 0;
	segmentArray[11].end_index = 9;
	segmentArray[11].total_length=segDistance(i83Sxa, i83Sya);
	segmentArray[11].numFollows = 2;
	//println(segmentArray[11].total_length);

	segmentArray[12] = new Segment;
	segmentArray[12].name = "i83S_2";
	segmentArray[12].x_array = i83Sxb;
	segmentArray[12].y_array = i83Syb;
	segmentArray[12].start_index = 0;
	segmentArray[12].end_index = 40;
	segmentArray[12].total_length=segDistance(i83Sxb, i83Syb);
	segmentArray[12].numFollows=1;
	//println(segmentArray[12].total_length);

	segmentArray[13] = new Segment;
	segmentArray[13].name = "i83S_3";
	segmentArray[13].x_array = i83Sxc;
	segmentArray[13].y_array = i83Syc;
	segmentArray[13].start_index = 0;
	segmentArray[13].end_index = 29;
	segmentArray[13].total_length=segDistance(i83Sxc, i83Syc);
	segmentArray[13].numFollows = 2;
	//println(segmentArray[13].total_length);

	segmentArray[14] = new Segment;
	segmentArray[14].name = "i83S_4";
	segmentArray[14].x_array = i83Sxd;
	segmentArray[14].y_array = i83Syd;
	segmentArray[14].start_index = 0;
	segmentArray[14].end_index = 39;
	segmentArray[14].total_length=segDistance(i83Sxd, i83Syd);
	segmentArray[14].numFollows = 1;
	//println(segmentArray[14].total_length);

	segmentArray[15] = new Segment;
	segmentArray[15].name = "i83S_5";
	segmentArray[15].x_array = i83Sxe;
	segmentArray[15].y_array = i83Sye;
	segmentArray[15].start_index = 0;
	segmentArray[15].end_index = 23;
	segmentArray[15].total_length=segDistance(i83Sxe, i83Sye);
	segmentArray[15].numFollows = 1;
	//println(segmentArray[15].total_length);

	segmentArray[16] = new Segment;
	segmentArray[16].name = "i55e83s_1";
	segmentArray[16].x_array = i55e83sXa;
	segmentArray[16].y_array = i55e83sYa;
	segmentArray[16].start_index = 0;
	segmentArray[16].end_index = 11;
	segmentArray[16].total_length=segDistance(i55e83sXa, i55e83sYa);
	segmentArray[16].numFollows = 2;
	//println(segmentArray[16].total_length);

	segmentArray[17] = new Segment;
	segmentArray[17].name = "i55e83s_2";
	segmentArray[17].x_array = i55e83sXb;
	segmentArray[17].y_array = i55e83sYb;
	segmentArray[17].start_index = 0;
	segmentArray[17].end_index = 17;
	segmentArray[17].total_length=segDistance(i55e83sXb, i55e83sYb);
	segmentArray[17].numFollows = 1;
	//println(segmentArray[17].total_length);

	segmentArray[18] = new Segment;
	segmentArray[18].name = "i55e83n_1";
	segmentArray[18].x_array = i55e83nXa;
	segmentArray[18].y_array = i55e83nYa;
	segmentArray[18].start_index = 0;
	segmentArray[18].end_index = 7;
	segmentArray[18].total_length=segDistance(i55e83nXa, i55e83nYa);
	segmentArray[18].numFollows = 1;
	//println(segmentArray[18].total_length);

	segmentArray[19] = new Segment;
	segmentArray[19].name = "i55e83n_2";
	segmentArray[19].x_array = i55e83nXb;
	segmentArray[19].y_array = i55e83nYb;
	segmentArray[19].start_index = 0;
	segmentArray[19].end_index = 4;
	segmentArray[19].total_length=segDistance(i55e83nXb, i55e83nYb);
	segmentArray[19].numFollows = 2;
	//println(segmentArray[19].total_length);

	segmentArray[20] = new Segment;
	segmentArray[20].name = "i55e83n_3";
	segmentArray[20].x_array = i55e83nXc;
	segmentArray[20].y_array = i55e83nYc;
	segmentArray[20].start_index = 0;
	segmentArray[20].end_index = 23;
	//segmentArray[20].total_length=segDistance(i55e83nXc, i55e83nYc); // not sure why this calculation doesn't work...
	segmentArray[20].total_length = 234.0;
	segmentArray[20].numFollows = 1;
	//println(segmentArray[20].total_length);

	segmentArray[21] = new Segment;
	segmentArray[21].name = "i55w83n_1";
	segmentArray[21].x_array = i55w83nXa;
	segmentArray[21].y_array = i55w83nYa;
	segmentArray[21].start_index = 0;
	segmentArray[21].end_index = 10;
	segmentArray[21].total_length=segDistance(i55w83nXa, i55w83nYa);
	segmentArray[21].numFollows = 2;
	//println(segmentArray[21].total_length);

	segmentArray[22] = new Segment;
	segmentArray[22].name = "i55w83n_2";
	segmentArray[22].x_array = i55w83nXb;
	segmentArray[22].y_array = i55w83nYb;
	segmentArray[22].start_index = 0;
	segmentArray[22].end_index = 17;
	segmentArray[22].total_length=segDistance(i55w83nXb, i55w83nYb);
	segmentArray[22].numFollows = 1;
	//println(segmentArray[22].total_length);

	segmentArray[23] = new Segment;
	segmentArray[23].name = "i55w83s_1";
	segmentArray[23].x_array = i55w83sXa;
	segmentArray[23].y_array = i55w83sYa;
	segmentArray[23].start_index = 0;
	segmentArray[23].end_index = 6;
	segmentArray[23].total_length=segDistance(i55w83sXa, i55w83sYa);
	segmentArray[23].numFollows = 1;
	//println(segmentArray[23].total_length);

	segmentArray[24] = new Segment;
	segmentArray[24].name = "i55w83s_2";
	segmentArray[24].x_array = i55w83sXb;
	segmentArray[24].y_array = i55w83sYb;
	segmentArray[24].start_index = 0;
	segmentArray[24].end_index = 6;
	segmentArray[24].total_length=segDistance(i55w83sXb, i55w83sYb);
	segmentArray[24].numFollows = 2;
	//println(segmentArray[24].total_length);

	segmentArray[25] = new Segment;
	segmentArray[25].name = "i55w83s_3";
	segmentArray[25].x_array = i55w83sXc;
	segmentArray[25].y_array = i55w83sYc;
	segmentArray[25].start_index = 0;
	segmentArray[25].end_index = 26;
	segmentArray[25].total_length=segDistance(i55w83sXc, i55w83sYc);
	segmentArray[25].numFollows = 1;
	//println(segmentArray[25].total_length);

	segmentArray[26] = new Segment;
	segmentArray[26].name = "i83n55w_1";
	segmentArray[26].x_array = i83n55wXa;
	segmentArray[26].y_array = i83n55wYa;
	segmentArray[26].start_index = 0;
	segmentArray[26].end_index = 21;
	segmentArray[26].total_length=segDistance(i83n55wXa, i83n55wYa);
	segmentArray[26].numFollows = 1;
	//println(segmentArray[26].total_length);

	segmentArray[27] = new Segment;
	segmentArray[27].name = "i83n55w_2";
	segmentArray[27].x_array = i83n55wXb;
	segmentArray[27].y_array = i83n55wYb;
	segmentArray[27].start_index = 0;
	segmentArray[27].end_index = 6;
	segmentArray[27].total_length=segDistance(i83n55wXb, i83n55wYb);
	segmentArray[27].numFollows = 1;
	//println(segmentArray[27].total_length);

	segmentArray[28] = new Segment;
	segmentArray[28].name = "i83n55e_1";
	segmentArray[28].x_array = i83n55eXa;
	segmentArray[28].y_array = i83n55eYa;
	segmentArray[28].start_index = 0;
	segmentArray[28].end_index = 34;
	segmentArray[28].total_length=segDistance(i83n55eXa, i83n55eYa);
	segmentArray[28].numFollows = 1;
	//println(segmentArray[28].total_length);

	segmentArray[29] = new Segment;
	segmentArray[29].name = "i83n55e_2";
	segmentArray[29].x_array = i83n55eXb;
	segmentArray[29].y_array = i83n55eYb;
	segmentArray[29].start_index = 0;
	segmentArray[29].end_index = 7;
	segmentArray[29].total_length=segDistance(i83n55eXb, i83n55eYb);
	segmentArray[29].numFollows = 1;
	//println(segmentArray[29].total_length);

	segmentArray[30] = new Segment;
	segmentArray[30].name = "i83s55e_1";
	segmentArray[30].x_array = i83s55eXa;
	segmentArray[30].y_array = i83s55eYa;
	segmentArray[30].start_index = 0;
	segmentArray[30].end_index = 24;
	segmentArray[30].total_length=segDistance(i83s55eXa, i83s55eYa);
	segmentArray[30].numFollows = 1;
	//println(segmentArray[30].total_length);

	segmentArray[31] = new Segment;
	segmentArray[31].name = "i83s55e_2";
	segmentArray[31].x_array = i83s55eXb;
	segmentArray[31].y_array = i83s55eYb;
	segmentArray[31].start_index = 0;
	segmentArray[31].end_index = 11;
	segmentArray[31].total_length=segDistance(i83s55eXb, i83s55eYb);
	segmentArray[31].numFollows = 1;
	//println(segmentArray[31].total_length);

	segmentArray[32] = new Segment;
	segmentArray[32].name = "i83s55w_1";
	segmentArray[32].x_array = i83s55wXa;
	segmentArray[32].y_array = i83s55wYa;
	segmentArray[32].start_index = 0;
	segmentArray[32].end_index = 37;
	//segmentArray[32].total_length=segDistance(i83s55wXa, i83s55wYa); //not sure why this calculation doesn't work...
	segmentArray[32].total_length = 330.0;
	segmentArray[32].numFollows = 1;
	//println(segmentArray[32].total_length);

	segmentArray[33] = new Segment;
	segmentArray[33].name = "i83s55w_2";
	segmentArray[33].x_array = i83s55wXb;
	segmentArray[33].y_array = i83s55wYb;
	segmentArray[33].start_index = 0;
	segmentArray[33].end_index = 7;
	segmentArray[33].total_length=segDistance(i83s55wXb, i83s55wYb);
	segmentArray[33].numFollows = 1;
	//println(segmentArray[33].total_length);

	segmentArray[0].follows[0]=segmentArray[1];
	segmentArray[0].follows[1]=segmentArray[16];

	segmentArray[1].follows[0]=segmentArray[2];

	segmentArray[2].follows[0]=segmentArray[0];

	segmentArray[3].follows[0]=segmentArray[4];
	segmentArray[3].follows[1]=segmentArray[21];

	segmentArray[4].follows[0]=segmentArray[5];

	segmentArray[5].follows[0]=segmentArray[3];

	segmentArray[6].follows[0]=segmentArray[7];
	segmentArray[6].follows[1]=segmentArray[28];

	segmentArray[7].follows[0]=segmentArray[8];

	segmentArray[8].follows[0]=segmentArray[9];
	segmentArray[8].follows[1]=segmentArray[26];

	segmentArray[9].follows[0]=segmentArray[10];

	segmentArray[10].follows[0]=segmentArray[6];

	segmentArray[11].follows[0]=segmentArray[12];
	segmentArray[11].follows[1]=segmentArray[32];

	segmentArray[12].follows[0]=segmentArray[13];

	segmentArray[13].follows[0]=segmentArray[14];
	segmentArray[13].follows[1]=segmentArray[30];

	segmentArray[14].follows[0]=segmentArray[15];

	segmentArray[15].follows[0]=segmentArray[11];

	segmentArray[16].follows[0]=segmentArray[17];
	segmentArray[16].follows[1]=segmentArray[18];

	segmentArray[17].follows[0]=segmentArray[15];

	segmentArray[18].follows[0]=segmentArray[19];

	segmentArray[19].follows[0]=segmentArray[20];
	segmentArray[19].follows[1]=segmentArray[31];

	segmentArray[20].follows[0]=segmentArray[8];

	segmentArray[21].follows[0]=segmentArray[22];
	segmentArray[21].follows[1]=segmentArray[23];

	segmentArray[22].follows[0]=segmentArray[10];

	segmentArray[23].follows[0]=segmentArray[24];

	segmentArray[24].follows[0]=segmentArray[25];
	segmentArray[24].follows[1]=segmentArray[27];

	segmentArray[25].follows[0]=segmentArray[13];

	segmentArray[26].follows[0]=segmentArray[24];

	segmentArray[27].follows[0]=segmentArray[33];

	segmentArray[28].follows[0]=segmentArray[29];

	segmentArray[29].follows[0]=segmentArray[2];

	segmentArray[30].follows[0]=segmentArray[19];

	segmentArray[31].follows[0]=segmentArray[29];

	segmentArray[32].follows[0]=segmentArray[33];

	segmentArray[33].follows[0]=segmentArray[5];
}

/*void setupPaths()
{
	Path path1 = new Path;
	path1.name="path1";
	path1.pathSegments = {segmentArray[0], segmentArray[1], segmentArray[2]};

	Path path2 = new Path;
	path2.name="path2";
	path2.pathSegments = {segmentArray[3], segmentArray[4], segmentArray[5]};

	Path path3 = new Path;
	path3.name="path3";
	path3.pathSegments = {segmentArray[6], segmentArray[7], segmentArray[8], segmentArray[9], segmentArray[10]};

	Path path4 = new Path;
	path4.name="path4";
	path4.pathSegments = {segmentArray[11], segmentArray[12], segmentArray[13], segmentArray[14], segmentArray[15]};

	Path path5 = new Path;
	path5.name="path5";
	path5.pathSegments = {segmentArray[0], segmentArray[16], segmentArray[17], segmentArray[15]};

	Path path6 = new Path;
	path6.name="path6";
	path6.pathSegments = {segmentArray[0], segmentArray[16], segmentArray[18], segmentArray[19], segmentArray[20],
							segmentArray[8], segmentArray[9], segmentArray[10]};

	Path path7 = new Path;
	path7.name="path7";
	path7.pathSegments = {segmentArray[3], segmentArray[21], segmentArray[22], segmentArray[10]};

	Path path8 = new Path;
	path8.name="path8";
	path8.pathSegments = {segmentArray[3], segmentArray[21], segmentArray[23], segmentArray[24], segmentArray[25],
							segmentArray[13], segmentArray[14], segmentArray[15]};

	Path path9 = new Path;
	path9.name="path9";
	path9.pathSegments = {segmentArray[6], segmentArray[7], segmentArray[8], segmentArray[26], segmentArray[24],
							segmentArray[27], segmentArray[33], segmentArray[5]};

	Path path10 = new Path;
	path10.name="path10";
	path10.pathSegments = {segmentArray[6], segmentArray[28], segmentArray[29], segmentArray[2]};

	Path path11 = new Path;
	path11.name="path11";
	path11.pathSegments = {segmentArray[11], segmentArray[12], segmentArray[13], segmentArray[30], segmentArray[19],
							segmentArray[31], segmentArray[29], segmentArray[2]};

	Path path12 = new Path;
	path12.name="path12";
	path12.pathSegments = {segmentArray[11], segmentArray[32], segmentArray[33], segmentArray[5]};

	Path path13 = new Path;
	path13.name="path13";
	path13.pathSegments = {segmentArray[3], segmentArray[21], segmentArray[23], segmentArray[24], segmentArray[27],
							segmentArray[33], segmentArray[5]};

	Path path14 = new Path;
	path14.name="path14";
	path14.pathSegments = {segmentArray[0], segmentArray[16], segmentArray[18], segmentArray[19], segmentArray[31],
							segmentArray[29], segmentArray[2]};

}*/


void setupCars()
{
	carArray[0] = new Car;
	carArray[0].id = "Mario";
	carArray[0].currSegment = "i55E_1";
	carArray[0].distance = 1.0;
	carArray[0].speed = 0.20;

	carArray[1] = new Car;
	carArray[1].id = "Luigi";
	carArray[1].currSegment = "i55W_1";
	carArray[1].distance = 1.0;
	carArray[1].speed = 0.20;

	carArray[2] = new Car;
	carArray[2].id = "Yoshi";
	carArray[2].currSegment = "i83N_1";
	carArray[2].distance = 1.0;
	carArray[2].speed = 0.10;

	carArray[3] = new Car;
	carArray[3].id = "PrincessPeach";
	carArray[3].currSegment = "i83S_1";
	carArray[3].distance = 1.0;
	carArray[3].speed = 0.10;

	carArray[4] = new Car;
	carArray[4].id = "Princess";
	carArray[4].currSegment = "i55W_2";
	carArray[4].distance = 1.0;
	carArray[4].speed = 0.10;

	carArray[5] = new Car;
	carArray[5].id = "Curvy";
	carArray[5].currSegment = "i55w83n_2";
	carArray[5].distance = 1.0;
	carArray[5].speed = 0.10;

	carArray[6] = new Car;
	carArray[6].id = "Curvy2";
	carArray[6].currSegment = "i55E_1";
	carArray[6].distance = 7.0;
	carArray[6].speed = 0.10;

	carArray[7] = new Car;
	carArray[7].id = "Curvy3";
	carArray[7].currSegment = "i55W_1";
	carArray[7].distance = 7.0;
	carArray[7].speed = 0.10;

	carArray[8] = new Car;
	carArray[8].id = "Curvy4";
	carArray[8].currSegment = "i83N_1";
	carArray[8].distance = 7.0;
	carArray[8].speed = 0.10;

	carArray[9] = new Car;
	carArray[9].id = "Curvy5";
	carArray[9].currSegment = "i83S_1";
	carArray[9].distance = 7.0;
	carArray[9].speed = 0.10;

	carArray[10] = new Car;
	carArray[10].id = "Granny";
	carArray[10].currSegment = "i83N_2";
	carArray[10].distance = 5.0;
	carArray[10].speed = 0.05;

	carArray[11] = new Car;
	carArray[11].id = "Grampy";
	carArray[11].currSegment = "i83S_2";
	carArray[11].distance = 5.0;
	carArray[11].speed = 0.05;

	carArray[12] = new Car;
	carArray[12].id = "Grampy";
	carArray[12].currSegment = "i83S_2";
	carArray[12].distance = 15.0;
	carArray[12].speed = 0.20;

	carArray[13] = new Car;
	carArray[13].id = "Grampy";
	carArray[13].currSegment = "i83S_2";
	carArray[13].distance = 35.0;
	carArray[13].speed = 0.20;

	carArray[14] = new Car;
	carArray[14].id = "Grampy";
	carArray[14].currSegment = "i83S_2";
	carArray[14].distance = 25.0;
	carArray[14].speed = 0.20;

	for(int ii = 0; ii < numCars; ii++)
	{
	  carArray[ii].desiredSpeed = carArray[ii].speed;
	  carArray[ii].carColorR = 255;
	  carArray[ii].carColorG = carArray[ii].carColorB = 0;
	}

	carArray[0].carColorG = 255;
	carArray[0].carColorR = carArray[0].carColorB = 0;
	carArray[1].carColorG = 255;
	carArray[1].carColorR = carArray[1].carColorB = 0;

	carArray[10].carColorB = 255;
	carArray[10].carColorR = carArray[10].carColorG = 0;
	carArray[11].carColorB = 255;
	carArray[11].carColorR = carArray[10].carColorG = 0;
}

void setup()
{
	size(795, 575);
	bg = loadImage("Background.png");
	
	setupSegments();
	//setupPaths();
	setupCars();
}


float distance(x1, y1, x2, y2)
{
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void drawCar(Car c)
{
  Segment currSeg;
  
  for(int ii = 0; ii < 34; ii++)
  {
      if(c.currSegment == segmentArray[ii].name)
      {
        currSeg = segmentArray[ii];
      }
  }
  
  float currDist = 0.0;
  float prevDist = 0.0;
  int currPoint = 0;
  
  //alert(currDist);
  //alert(c.distance);
  //alert(currPoint);
  //alert(currSeg.end_index);
  
  while(currDist < c.distance && currPoint < currSeg.end_index)
  {
    currDist += distance(currSeg.x_array[currPoint], currSeg.y_array[currPoint],
    					currSeg.x_array[currPoint+1], currSeg.y_array[currPoint+1]);
    currPoint++;
    if(currDist < c.distance)
    {
      prevDist = currDist;
    }
  }
  
  /*if(currPoint == 0)
  {
    // negative or 0 distance for the car. ABORT!
    return;
  }*/
  
  //alert(c.distance + currPoint + ", " + prevDist + ", ");
  
  	float distanceBetweenPoints = currDist - prevDist;
  	float carBetweenPoints = c.distance - prevDist;
  	float carFractionTravelled = carBetweenPoints / distanceBetweenPoints;
  
  
  
  	c.car_x = currSeg.x_array[currPoint -1]*(1-carFractionTravelled) +
  								currSeg.x_array[currPoint]*carFractionTravelled;
  	c.car_y = currSeg.y_array[currPoint -1]*(1-carFractionTravelled) +
  								currSeg.y_array[currPoint]*carFractionTravelled;
  
  
  //alert("prev point" + currSeg.x_array[currPoint -1] + ", " + currSeg.y_array[currPoint -1]);
  //alert("prev point" + currSeg.x_array[currPoint] + ", " + currSeg.y_array[currPoint]);
  //alert("car" + car_x + ", " + car_y);
  
		//fill(255, 0, 0);
		fill(c.carColorR, c.carColorG, c.carColorB);
		noStroke();
		rect(c.car_x, 570-c.car_y-4, 5, 5);

}

float infinity = 10000000.0;

float nearestCar(car c)
{
	float minDistance = infinity;
	for(int i = 0; i< numCars; i++)
	{
		//if cars are on same segment check their distance
		if(carArray[i].currSegment == c.currSegment)
		{
			float distance = carArray[i].distance - c.distance;
			if(distance > 0)
			{
				if(minDistance > distance)
				{
					minDistance = distance
				}
			}

		}
	}
	return minDistance;
}

float reactFunc(float speed, float desiredSpeed, float distance)
{
	float reactionDistance = 150.0;
	if(distance < speed * reactionDistance)
	{
		return -speed/5.0; //slow down more quickly the closer the car is
	}
	else
	{
		return 0.001; //speed up more slowly if there's a car ahead
	}

}

void updateCar(Car c, int dt)
{
	Segment currSeg;
	int segNum;
  for(int ii = 0; ii < 34; ii++)
  {
      if(c.currSegment == segmentArray[ii].name)
      {
        currSeg = segmentArray[ii];
        segNum=ii;
        //println(currSeg.name);
      }
  }

  float distanceAhead = nearestCar(c);
  c.speed += reactFunc(c.speed, c.desiredSpeed, distanceAhead);
  if(c.speed < 0)
  {
  	c.speed = 0.0;
  }
  if(c.speed > c.desiredSpeed)
  {
  	c.speed = c.desiredSpeed;
  }


  c.distance += c.speed * dt; // should probably be: speed * dt
  if(c.distance > currSeg.total_length)
  {
    c.distance = 0.01;
    int randInt = int(random(10)%segmentArray[segNum].numFollows);
    c.currSegment = segmentArray[segNum].follows[randInt];
    c.currSegment = segmentArray[segNum].follows[randInt].name;
  }
}


void updateSimulation()
{
  int m = millis();

  if(m>lastUpdateTime+20)
  {
    int dt = m - lastUpdateTime;
    lastUpdateTime = m;
    for(int ii=0; ii<numCars; ii++) {
      updateCar(carArray[ii], dt);
    }
  }
}

//just for debugging...
/*void drawCarPaths()
{
	// car paths for debugging...
	for(int i = 0; i<i55Ex.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55Ex[i], 570-i55Ey[i]-4, 2, 2);
	}

	for(int i = 0; i<i55Wx.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55Wx[i], 570-i55Wy[i]-4, 2, 2);
	}

	for(int i = 0; i<i83Nx.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83Nx[i]+4, 570-i83Ny[i], 2, 2);
	}

	for(int i = 0; i<i83Sx.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83Sx[i]+4, 570-i83Sy[i], 2, 2);
	}

	for(int i = 0; i<i55e83sX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55e83sX[i], 570-i55e83sY[i]+2, 2, 2);
	}

	for(int i = 0; i<i55e83nX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55e83nX[i], 570-i55e83nY[i]+2, 2, 2);
	}

	for(int i = 0; i<i55w83nX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55w83nX[i], 570-i55w83nY[i]+2, 2, 2);
	}

	for(int i = 0; i<i55w83sX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i55w83sX[i], 570-i55w83sY[i]+2, 2, 2);
	}

	for(int i = 0; i<i83n55wX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83n55wX[i], 570-i83n55wY[i]+2, 2, 2);
	}

	for(int i = 0; i<i83n55eX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83n55eX[i], 570-i83n55eY[i]+2, 2, 2);
	}

	for(int i = 0; i<i83s55eX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83s55eX[i], 570-i83s55eY[i]+2, 2, 2);
	}

	for(int i = 0; i<i83s55wX.length(); i++)
	{
		fill(0, 121, 184);
		noStroke();
		rect(i83s55wX[i], 570-i83s55wY[i]+2, 2, 2);
	}
}*/

void draw()
{
  updateSimulation();
  
	background(bg);

	for(int i=0; i<numCars; i++)
	{
		drawCar(carArray[i]);
	}
}
