from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    # verifica se há lugar no buffer
    lugar_no_buffer.acquire()
    buffer.append(item)
    item_no_buffer.release()
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))

def consumidor():
  global buffer
  for i in range(10):
    item_no_buffer.acquire()
    item = buffer.pop(0)
    lugar_no_buffer.release()
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 3
# cria semáforos
lugar_no_buffer = Semaphore(tam_buffer)
item_no_buffer = Semaphore(0)
produtor = Thread(target=produtor) 
consumidor = Thread(target=consumidor) 
produtor.start()
consumidor.start()
produtor.join()
consumidor.join() 