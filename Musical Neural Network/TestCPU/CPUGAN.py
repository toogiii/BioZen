from pycomposer.gancomposable._mxnet.conditional_gan_composer import ConditionalGANComposer
import mxnet as mx
import glob

from logging import getLogger, StreamHandler, NullHandler, DEBUG, ERROR
logger = getLogger("accelbrainbase")
handler = StreamHandler()
handler.setLevel(DEBUG)
logger.setLevel(DEBUG)
logger.addHandler(handler)
import matplotlib.pyplot as plt
#%matplotlib inline
#import seaborn as sns
#%config InlineBackend.figure_format = "retina"
plt.style.use("fivethirtyeight")
#print([i for i in glob.glob("/content/gdrive/MyDrive/Unison Free Mini MIDI Pack/*/*/*/*")])
gan_composer = ConditionalGANComposer(
    midi_path_list = [i for i in glob.glob(r"C:\Users\garvg\OneDrive\Documents\GitHub\BioZen\Musical Neural Network\TestCPU\MIDI\*.mid")],
    batch_size = 20,
    seq_len = 16,
    learning_rate = 1e-10,
    time_fraction = 0.5
)
gan_composer.generative_model.model.load_parameters(filename=r"C:\Users\garvg\OneDrive\Documents\GitHub\BioZen\Musical Neural Network\TestCPU\Lambdas\330min.params", ctx=mx.cpu())
gan_composer.learn(
    iter_n = 10,
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
    file_path = r'test.mid',
    velocity_mean = 70,
    velocity_std = 10
)

gan_composer.generative_model.model.save_parameters(filename="test.params")