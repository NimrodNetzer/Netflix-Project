FROM python:3.9-slim

WORKDIR /app

COPY test.py /app/

COPY requirements.txt /app/

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

ENTRYPOINT ["python", "test.py"]