## Covid-19 Image Dataset

### Dataset includes X-ray images for individuals that have covid, pneumonia, or are normal. Goal is to identify each image correctly using ResNet-34 and ResNet-50 models.
### First iteration resized images to 224x224, and transformed data using one-hot-encoding. Second iteration did the same using ImageDataGenerator which is a data preprocessing utility provided by Keras.
### ResNet allows us to train extremely deep neural networks without the vanishing gradient problem. ResNet uses skip connection, which jumps over layers to relay input. This helps prevent the gradient from becoming too small

## Results:
### Overfitting due to the low number of samples, minimal data augmentation, and complexity of ResNet
### Training accuracy > 90%, but Testing accuracy limited to < 50%
### Final prediction only predicts 1-2 classes for all implementations done
