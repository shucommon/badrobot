import numpy as np
import pandas as pd

df = pd.DataFrame({'var1':np.random.rand(100),
                    'var2':100,
                    'var3':np.random.choice([20, 30, 90])})

df
