code file.py   -> creates a new python file (Type in terminal)
python file.py -> To get Output

🔴🟡🟢
1. Create API key from OpenAI
2. Download Python Manager
3.Collaab With VS Code & Download the python Etension From Microsoft.
$. Enter this cod in terminal :

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
