code file.py   -> creates a new python file (Type in terminal)
python file.py -> To get Output


----------------------------------------------------------------------------------------------------------------------------------------------------------------------
from openai import OpenAI

client = OpenAI()

response = client.responses.create(
    input="In one sentence, what is CS50?",
    model="gpt-5"
)
print(response.output_text)
