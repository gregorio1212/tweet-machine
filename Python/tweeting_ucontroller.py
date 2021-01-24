 # @file tweeting_ucrocontroller.c
 # @author Gregório da Luz
 # @date January 2021
 # @brief file to tweet through microcontroller
import serial
import tweepy

key = "x90redHO7n2gRHn1IpSc8Vcor"
secret = "CmxFBjpo6uuqFhCGi6NRFAo2U7fdZx3dUmLkRx5Z8lnEa27Dwb"
access_token = "1352355518086582272-cf3da0erLLD3RvVzUjCM6lCcjmPMcD"
access_token_secret = "1k1kPXPmilplIHXPvKUis9cZso17j8IA63WhWk4kuDUlQ"

ser = serial.Serial('COM5', 9600,timeout=1)
tweet_limit = 0

def OAuth():
    try:
        auth = tweepy.OAuthHandler(key, secret)
        auth.set_access_token(access_token, access_token_secret)
        return auth
    except Exception as e:
        return None

oauth = OAuth()
api = tweepy.API(oauth)

while(tweet_limit < 5):
    tweet = ser.readline()
    if(tweet !=b''):
        api.update_status(tweet)
        tweet_limit +=1
