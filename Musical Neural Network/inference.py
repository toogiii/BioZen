from pycomposer.gancomposable._mxnet.conditional_gan_composer import ConditionalGANComposer
import mxnet as mx
import glob

def get_composer(param_file):
    gan_composer = ConditionalGANComposer(
        midi_path_list = [i for i in glob.glob(r"C:\Users\garvg\OneDrive\Documents\GitHub\BioZen\Musical Neural Network\MIDI\*.mid")],
        batch_size = 20,
        seq_len = 16,
        learning_rate = 1e-10,
        time_fraction = 0.5
    )
    gan_composer.generative_model.model.load_parameters(filename=param_file)
    return gan_composer

def compose_music(out_file):
    gan_composer.compose(
        file_path = out_file,
        velocity_mean = 70,
        velocity_std = 10
    )    