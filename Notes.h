                                                              Introducton TO Harvard University - CS50 edX

                                                                                 
code file.py   -> creates a new python file (Type in terminal)
python file.py -> To get Output

🔴🟡🟢
1. Create API key from OpenAI
2. Download Python Manager
3.Collaab With VS Code & Download the python Etension From Microsoft.
$. Enter this code in terminal :

CS50 AI : https://cs50.ai/chat 
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Creating Our Own AI Chatbot
    
from openai import OpenAI

client = OpenAI()

response = client.responses.create(
    input="In one sentence, what is CS50?",
    model="gpt-5"
)
print(response.output_text)


--------------------------------------------------------------------------------------------------------------
    from openai import OpenAI

client = OpenAI()

user_prompt = input("Prompt: ")
system_prompt = "Limit your answer to one sentence. Pretend you're a cat."

response = client.responses.create(
    input=user_prompt,
    instructions=system_prompt,
    model="gpt-5"
)

print(response.output_text)


--------------------------------------------------------------------------------------------------

                  ASCII Code
    
    65-A                              97-a
    66-B                              98-b
    .                                 .
    .                                 .
    .                                 .
    .                                 .
    .                                 .
    .                                 .
    .                                 .
    .                                 .
    90-Z                               122-z

    A-Z :: 65-90                          a-z :: 97-122

    In This The DIfference will a;ways be 32 so the 32 will be changed and res be the same
     
                     A                                                            a
    128   64    32    16    8      4     2     1               128   64    32    16    8      4     2     1
    0     1     0     0     0      0     0     1                0     1     1     0     0      0     0     1  
                ^                                                           ^
                |                                                           |



  Dec	Chr		Dec	Chr		  Dec	Chr	      	Dec	Chr	     	Dec	Chr	       	Dec	Chr		    Dec	Chr		     Dec	Chr
  0 -	NUL		16 -	DLE		32 -	SP		48 -	0		64 -	@		80 -	P		96 -	`		112 -	p
  1 -	SOH		17 -	DC1		33 -	!		49 -	1	  🔴65 -	A		81 -	Q	  🔴97 -	a		113 -	q
  2 -	STX		18 -	DC2		34 -	”		50 -	2		66 -	B		82 -	R		98 -	b		114 -	r
  3 -	ETX		19 -	DC3		35 -	#		51 -	3		67 -	C		83 -	S		99 -	c		115 -	s
  4 -	EOT		20 -	DC4		36 -	$		52 -	4		68 -	D		84 -	T		100 -	d		116 -	t
  5 -	ENQ		21 -	NAK		37 -	%		53 -	5		69 -	E		85 -	U		101 -	e		117 -	u
  6 -	ACK		22 -	SYN		38 -	&		54 -	6		70 -	F		86 -	V		102 -	f		118 -	v
  7 -	BEL		23 -	ETB		39 -	’		55 -	7		71 -	G		87 -	W		103 -	g		119 -	w
  8 -	BS		24 -	CAN		40 -	(		56 -	8		72 -	H		88 -	X		104 -	h		120 -	x
  9 -	HT		25 -	EM		41 -	)		57 -	9		73 -	I		89 -	Y		105 -	i		121 -	y
  10 -	LF	    26 -	SUB		42 -	*		58 -	:	    74 -	J	  🟢90 -	Z		106 -	j	  🟢122 -	z
  11 -	VT		27 -	ESC		43 -	+		59 -	;	    75 -	K		91 -	[		107 -	k		123 -	{
  12 -	FF		28 -	FS		44 -	,		60 -	<	    76 -	L		92 -	\		108 -	l		124 -	|
  13 -	CR		29 -	GS		45 -	-		61 -	=	    77 -	M		93 -	]		109 -	m		125 -	}
  14 -	SO		30 -	RS		46 -	.		62 -	>	    78 -	N		94 -	^		110 -	n		126 -	~
  15 -	SI		31 -	US		47 -	/		63 -	?	    79 -	O		95 -	_		111 -	o		127 -	DEL


  

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Unicode
As time has rolled on, there are more and more ways to communicate via text.
Since there were not enough digits in binary to represent all the various characters that could be represented by humans, the Unicode standard expanded the number of bits that can be transmitted and understood by computers. Unicode includes not only special characters, but emoji as well.
There are emoji that you probably use every day. The following may look familiar to you:

😀 😃 😄 😁 😆 😅 😂 🙂 🙃 😉 😊 😇 😍 😘 😗 😙 😚 😋 😛 😜 😝 🤑 🤓 😎 🤗 😏 😶 😐 😑 😒 🙄 😬 😕 ☹️ 😟 😮 😯 😲 😳 😦 😧 😨

While the pattern of zeros and ones is standardized within Unicode, each device manufacturer may display each emoji slightly differently than another manufacturer.
More and more features are being added to the Unicode standard to represent further characters and emoji.
If you wish, you can learn more about Unicode.
If you wish, you can learn more about emoji.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  RGB
Zeros and ones can be used to represent color.
Red, green, and blue (called RGB) are a combination of three numbers.

72 73 33
Taking our previously used 72, 73, and 33, which said HI! via text, would be interpreted by image readers as a light shade of yellow. The red value would be 72, the green value would be 73, and the blue would be 33.
The three bytes required to represent various colors of red, blue, and green (or RGB) make up each pixel (or dot) of color in any digital image. Images are simply collections of RGB values.
Zeros and ones can be used to represent images, videos, and music!
Videos are sequences of many images that are stored together, just like a flipbook.
Music can be represented similarly using various combinations of bytes.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
