import matplotlib.pyplot as plt
import mxnet as mx
import seaborn as sns
plt.style.use('fivethirtyeight')
from pycomposer.gancomposable._mxnet.conditional_gan_composer import ConditionalGANComposer
from logging import getLogger, StreamHandler, NullHandler, DEBUG, ERROR

logger = getLogger('pygan')
handler = StreamHandler()
handler.setLevel(DEBUG)
logger.setLevel(DEBUG)
logger.addHandler(handler)

gan_composer = ConditionalGANComposer(
    midi_path_list = [
        r'C:\Users\garvg\Downloads\Michael_Jackson_-_Smooth_Criminal.mid'
    ],
    batch_size = 20,
    seq_len = 8,
    learning_rate = 1e-10,
    time_fraction = 0.5,
    ctx = mx.cpu()
)

gan_composer.learn(
    iter_n = 1000,
    k_step = 10
)


generative_loss_arr, discriminative_loss_arr, posterior_logs_arr, feature_matching_loss_arr  = gan_composer.extract_logs()
plt.figure(figsize=(20, 10))

plt.plot(posterior_logs_arr)
plt.title("Logs of posteriors")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.show()


gan_composer.compose(
    file_path = r'path\to\new\midi\file.mid',
    velocity_mean = None,
    velocity_std = None
)


gan_composer.generative_model.model.save_parameters(filename="demo_midinet.params")
#gan_composer.generative_model.model.load_parameters(filename="demo_midinet.params", ctx=mx.gpu())