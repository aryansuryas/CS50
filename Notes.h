code file.py   -> creates a new python file (Type in terminal)
python file.py -> To get Output

🔴🟡🟢
1. Create API key from OpenAI
2. Download Python Manager
3.Collaab With VS Code & Download the python Etension From Microsoft.
$. Enter this cod in terminal :
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    
from openai import OpenAI

client = OpenAI()

response = client.responses.create(
    input="In one sentence, what is CS50?",
    model="gpt-5"
)
print(response.output_text)


    -------------------------------------------------------------------
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
