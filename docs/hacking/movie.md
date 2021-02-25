# The Movie

[https://youtu.be/A-kYHdrr-Mg](https://youtu.be/A-kYHdrr-Mg)

or

oswatchclip.mp4

## editing :

Kdenlive

## script :

LibreOffice Impress

## Camera :

SimpleScreenRecorder

## Voice over :

espeak -v en+f5 -a 100 -p 50 -s 110 -f slide2.txt -w slide2.wav

## Music by Beethoven:

fluidsynth -a pulseaudio -o audio.alsa.device=hw:1 -m alsa_seq -l -i /usr/share/sounds/sf2/FluidR3_GM.sf2 moonlight_sonata.mid

this one works best :
timidity moonlight_sonata.mid -Ow -o out.wav
