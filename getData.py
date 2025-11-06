#Script description: Get Data (Temp and Hum) from Arduino
import serial
import time
import os

from supabase import create_client, Client
from getPort import port

url = "https://ckososjoitleuizzcyqv.supabase.co"
key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImNrb3Nvc2pvaXRsZXVpenpjeXF2Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjA2MjMwNTMsImV4cCI6MjA3NjE5OTA1M30.RpK_cqHb5JO9s4urUnx1pc8thypYpgBSSfvyA-PlunE"
supabase: Client = create_client(url, key)

arduino_port = port # Don't worry by the port
baud_rate = 9600 # Baudios
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

time.sleep(2)

while True:
    data = ser.readline().decode('utf-8').rstrip()
    #print(data)
    if data:
        try:
            humidity, temperature = data.split(",")
            humidity = float(humidity)
            temperature = float(temperature)

            # --- ENVÍO A SUPABASE ---
            response = supabase.table("data").insert({
                "humidity": humidity,
                "temperature": temperature
            }).execute()

            print("✅ Datos enviados:", humidity, temperature)
        except ValueError:
            print("⚠️ Formato de datos inválido:", data)
        except Exception as e:
            print("❌ Error al enviar a Supabase:", e)
    time.sleep(1)